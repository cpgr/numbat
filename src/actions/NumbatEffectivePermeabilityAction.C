/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatEffectivePermeabilityAction.h"
#include "FEProblem.h"
#include "AddVariableAction.h"
#include "MooseApp.h"
#include "MooseMesh.h"
#include "ActionWarehouse.h"
#include "ActionFactory.h"
#include "MooseObjectAction.h"
#include "MooseUtils.h"

#include "libmesh/string_to_enum.h"

registerMooseAction("NumbatApp", NumbatEffectivePermeabilityAction, "add_variable");
registerMooseAction("NumbatApp", NumbatEffectivePermeabilityAction, "add_aux_variable");
registerMooseAction("NumbatApp", NumbatEffectivePermeabilityAction, "add_kernel");
registerMooseAction("NumbatApp", NumbatEffectivePermeabilityAction, "add_bc");
registerMooseAction("NumbatApp", NumbatEffectivePermeabilityAction, "add_material");
registerMooseAction("NumbatApp", NumbatEffectivePermeabilityAction, "add_postprocessor");

template <>
InputParameters
validParams<NumbatEffectivePermeabilityAction>()
{
  InputParameters params = validParams<Action>();
  MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
  MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());
  params.addParam<MooseEnum>(
      "family", families, "Specifies the family of FE shape functions to use for this variable");
  params.addParam<MooseEnum>("order",
                             orders,
                             "Specifies the order of the FE shape function to use "
                             "for this variable (additional orders not listed are "
                             "allowed)");
  params.addParam<Real>("scaling", 1.0, "Specifies a scaling factor to apply to this variable");
  MooseEnum direction("x=0 y=1 z=2");
  params.addRequiredParam<MooseEnum>(
      "direction", direction, "The spatial direction of the desired effective permeability");
  params.addRequiredParam<BoundaryName>("boundary_inflow", "Name of the inflow boundary");
  params.addRequiredParam<BoundaryName>("boundary_outflow", "Name of the outflow boundary");
  params.addParam<Real>("pressure_inflow", 2, "Pressure at the inflow boundary");
  params.addParam<Real>("pressure_outflow", 1, "Pressure at the outflow boundary");
  params.addClassDescription("Action to automatically add all variables, kernels, boundary "
                             "conditions and postprocessors to calculate effective permeability");
  return params;
}

NumbatEffectivePermeabilityAction::NumbatEffectivePermeabilityAction(
    const InputParameters & parameters)
  : Action(parameters),
    _fe_type(Utility::string_to_enum<Order>(getParam<MooseEnum>("order")),
             Utility::string_to_enum<FEFamily>(getParam<MooseEnum>("family"))),
    _scaling(getParam<Real>("scaling")),
    _pressure("pressure"),
    _concentration("concentration"),
    _direction(getParam<MooseEnum>("direction")),
    _pressure_inflow(getParam<Real>("pressure_inflow")),
    _pressure_outflow(getParam<Real>("pressure_outflow")),
    _boundary_inflow(getParam<BoundaryName>("boundary_inflow")),
    _boundary_outflow(getParam<BoundaryName>("boundary_outflow"))
{
}

void
NumbatEffectivePermeabilityAction::act()
{
  switch (_direction)
  {
    case 0:
      _velocity = "u";
      break;

    case 1:
      _velocity = "v";
      break;

    case 2:
      _velocity = "w";
      break;
  }

  _width = _mesh.get()->dimensionWidth(_direction);

  if (_current_task == "add_variable")
  {
    _problem->addVariable(_pressure, _fe_type, _scaling);
  }

  if (_current_task == "add_aux_variable")
  {
    // The AuxVariable for velocity has to be monomial
    const FEType _aux_fe_type(Utility::string_to_enum<Order>("constant"),
                              Utility::string_to_enum<FEFamily>("monomial"));

    _problem->addAuxVariable(_velocity, _aux_fe_type);

    // Dummy AuxVariable for concentration
    _problem->addAuxVariable(_concentration, _aux_fe_type);
  }

  if (_current_task == "add_kernel")
  {
    // Darcy kernel for pressure (with gravity equal to 0)
    std::string kernel_type = "NumbatDarcy";
    std::string kernel_name = "NumbatDarcy";
    InputParameters params = _factory.getValidParams(kernel_type);
    params.set<NonlinearVariableName>("variable") = _pressure;
    params.set<std::vector<VariableName>>("concentration") = {_concentration};
    const RealVectorValue gravity(0.0, 0.0, 0.0);
    params.set<RealVectorValue>("gravity") = gravity;
    _problem->addKernel(kernel_type, kernel_name, params);

    // AuxKernel for velocity (with gravity equal to 0)
    std::string auxkernel_type = "NumbatDarcyVelocity";
    std::string auxkernel_name = "NumbatDarcyVelocity_" + _velocity;
    params = _factory.getValidParams(auxkernel_type);
    params.set<std::vector<VariableName>>("pressure") = {_pressure};
    params.set<AuxVariableName>("variable") = _velocity;
    params.set<MooseEnum>("component") = _direction;
    params.set<RealVectorValue>("gravity") = gravity;
    _problem->addAuxKernel(auxkernel_type, auxkernel_name, params);
  }

  if (_current_task == "add_material")
  {
    // Generic properties for fluid density and viscosity
    std::string material_type = "GenericConstantMaterial";
    std::string material_name = "constant_fluid_properties";
    InputParameters params = _factory.getValidParams(material_type);
    params.set<std::vector<std::string>>("prop_names") = {"density", "viscosity"};
    params.set<std::vector<Real>>("prop_values") = {1.0, 1.0};
    _problem->addMaterial(material_type, material_name, params);
  }

  if (_current_task == "add_bc")
  {
    // Constant pressure at inflow boundary
    std::string bc_type = "PresetBC";
    std::string bc_name = "pressure_inflow";
    InputParameters params = _factory.getValidParams(bc_type);
    params.set<NonlinearVariableName>("variable") = _pressure;
    params.set<std::vector<BoundaryName>>("boundary") = {_boundary_inflow};
    params.set<Real>("value") = _pressure_inflow;
    _problem->addBoundaryCondition(bc_type, bc_name, params);

    // Constant pressure at outflow boundary
    bc_type = "PresetBC";
    bc_name = "pressure_outflow";
    params = _factory.getValidParams(bc_type);
    params.set<NonlinearVariableName>("variable") = _pressure;
    params.set<std::vector<BoundaryName>>("boundary") = {_boundary_outflow};
    params.set<Real>("value") = _pressure_outflow;
    _problem->addBoundaryCondition(bc_type, bc_name, params);
  }

  if (_current_task == "add_postprocessor")
  {
    // Area postprocessor
    std::string postprocessor_type = "AreaPostprocessor";
    std::string postprocessor_name = "area";
    InputParameters params = _factory.getValidParams(postprocessor_type);
    params.set<std::vector<BoundaryName>>("boundary") = {_boundary_outflow};
    params.set<ExecFlagEnum>("execute_on") = {EXEC_INITIAL, EXEC_TIMESTEP_END};
    _problem->addPostprocessor(postprocessor_type, postprocessor_name, params);

    // Side flux postprocessor
    postprocessor_type = "SideIntegralVariablePostprocessor";
    postprocessor_name = "flux";
    params = _factory.getValidParams(postprocessor_type);
    params.set<std::vector<VariableName>>("variable") = {_velocity};
    params.set<std::vector<BoundaryName>>("boundary") = {_boundary_outflow};
    params.set<ExecFlagEnum>("execute_on") = {EXEC_INITIAL, EXEC_TIMESTEP_END};
    _problem->addPostprocessor(postprocessor_type, postprocessor_name, params);

    // Effective permeability postprocessor
    postprocessor_type = "NumbatEffectivePermeability";
    postprocessor_name = "eff_perm";
    params = _factory.getValidParams(postprocessor_type);
    params.set<PostprocessorName>("flux") = "flux";
    params.set<PostprocessorName>("area") = "area";
    params.set<Real>("p1") = _pressure_inflow;
    params.set<Real>("p2") = _pressure_outflow;
    params.set<MooseEnum>("component") = _direction;
    params.set<ExecFlagEnum>("execute_on") = {EXEC_INITIAL, EXEC_TIMESTEP_END};
    _problem->addPostprocessor(postprocessor_type, postprocessor_name, params);
  }
}
