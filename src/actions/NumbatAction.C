/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatAction.h"
#include "FEProblem.h"
#include "AddVariableAction.h"
#include "MooseApp.h"
#include "MooseMesh.h"
#include "ActionWarehouse.h"
#include "ActionFactory.h"
#include "MooseObjectAction.h"
#include "MooseUtils.h"

#include "libmesh/string_to_enum.h"

registerMooseAction("NumbatApp", NumbatAction, "add_variable");
registerMooseAction("NumbatApp", NumbatAction, "add_aux_variable");
registerMooseAction("NumbatApp", NumbatAction, "add_kernel");
registerMooseAction("NumbatApp", NumbatAction, "add_bc");
registerMooseAction("NumbatApp", NumbatAction, "add_periodic_bc");
registerMooseAction("NumbatApp", NumbatAction, "add_postprocessor");

InputParameters
NumbatAction::validParams()
{
  InputParameters params = Action::validParams();
  MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
  MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());
  params.addParam<MooseEnum>(
      "family", families, "Specifies the family of FE shape functions to use for this variable");
  params.addParam<MooseEnum>("order",
                             orders,
                             "Specifies the order of the FE shape function to use "
                             "for this variable (additional orders not listed are "
                             "allowed)");
  params.addParam<Real>("concentration_scaling",
                        1.0,
                        "Specifies a scaling factor to apply to the concentration variable");
  params.addParam<Real>(
      "pressure_scaling", 1.0, "Specifies a scaling factor to apply to the pressure variable");
  params.addParam<Real>(
      "boundary_concentration", 1, "Concentration at constant-concentration boundary");
  params.addParam<bool>("periodic_bcs", true, "Whether to add periodic boundary conditions");
  RealVectorValue g(0, 0, -9.81);
  params.addParam<RealVectorValue>(
      "gravity", g, "Gravity vector. Defaults to -9.81 in y direction for 2D, z direction for 3D");
  params.addClassDescription("Action to automatically add all variables, kernels, boundary "
                             "conditions and postprocessors for the dimensional formulation");
  return params;
}

NumbatAction::NumbatAction(const InputParameters & parameters)
  : Action(parameters),
    _fe_type(Utility::string_to_enum<Order>(getParam<MooseEnum>("order")),
             Utility::string_to_enum<FEFamily>(getParam<MooseEnum>("family"))),
    _concentration_scaling(getParam<Real>("concentration_scaling")),
    _pressure_scaling(getParam<Real>("pressure_scaling")),
    _concentration("concentration"),
    _pressure("pressure"),
    _boundary_concentration(getParam<Real>("boundary_concentration")),
    _periodic_bcs(getParam<bool>("periodic_bcs")),
    _gravity(getParam<RealVectorValue>("gravity"))
{
}

void
NumbatAction::act()
{
  const unsigned int dim = _mesh.get()->dimension();

  // If gravity hasn't been provided, use a value of -9.81 in the y direction
  // for 2D, or in the z direction for 3D (which is the default)
  if (!_pars.isParamSetByUser("gravity"))
    if (dim == 2)
      _gravity = RealVectorValue(0, -9.81, 0);

  if (dim == 2)
    _aux = {"u", "v"};

  if (dim == 3)
    _aux = {"u", "v", "w"};

  if (_current_task == "add_variable")
  {
    const auto variable_type = AddVariableAction::variableType(_fe_type);
    {
      auto params = _factory.getValidParams(variable_type);
      params.applySpecificParameters(_pars, {"order", "family"});
      params.set<std::vector<Real>>("scaling") = {_concentration_scaling};
      _problem->addVariable(variable_type, _concentration, params);
    }
    {
      auto params = _factory.getValidParams(variable_type);
      params.applySpecificParameters(_pars, {"order", "family"});
      params.set<std::vector<Real>>("scaling") = {_pressure_scaling};
      _problem->addVariable(variable_type, _pressure, params);
    }
  }

  if (_current_task == "add_aux_variable")
  {
    const FEType _aux_fe_type(Utility::string_to_enum<Order>("constant"),
                              Utility::string_to_enum<FEFamily>("monomial"));
    const auto variable_type = AddVariableAction::variableType(_aux_fe_type);
    for (auto auxvar : _aux)
    {
      auto params = _factory.getValidParams(variable_type);
      params.set<MooseEnum>("family") = "monomial";
      params.set<MooseEnum>("order") = "constant";
      _problem->addAuxVariable(variable_type, auxvar, params);
    }
  }

  if (_current_task == "add_kernel")
  {
    // Time derivative kernel for concentration
    std::string kernel_type = "NumbatTimeDerivative";
    std::string kernel_name = "NumbatTimeDerivative";
    InputParameters params = _factory.getValidParams(kernel_type);
    params.set<NonlinearVariableName>("variable") = _concentration;
    _problem->addKernel(kernel_type, kernel_name, params);

    // Convection kernel for concentration
    kernel_type = "NumbatConvection";
    kernel_name = "NumbatConvection";
    params = _factory.getValidParams(kernel_type);
    params.set<NonlinearVariableName>("variable") = _concentration;
    params.set<std::vector<VariableName>>("pressure") = {_pressure};
    params.set<RealVectorValue>("gravity") = _gravity;
    _problem->addKernel(kernel_type, kernel_name, params);

    // Diffusion kernel for concentration
    kernel_type = "NumbatDiffusion";
    kernel_name = "NumbatDiffusion";
    params = _factory.getValidParams(kernel_type);
    params.set<NonlinearVariableName>("variable") = _concentration;
    _problem->addKernel(kernel_type, kernel_name, params);

    // Darcy kernel for pressure
    kernel_type = "NumbatDarcy";
    kernel_name = "NumbatDarcy";
    params = _factory.getValidParams(kernel_type);
    params.set<NonlinearVariableName>("variable") = _pressure;
    params.set<std::vector<VariableName>>("concentration") = {_concentration};
    params.set<RealVectorValue>("gravity") = _gravity;
    _problem->addKernel(kernel_type, kernel_name, params);

    // AuxKernels for velocity components
    for (unsigned int i = 0; i < _aux.size(); ++i)
    {
      std::string auxkernel_type = "NumbatDarcyVelocity";
      std::string auxkernel_name = "NumbatDarcyVelocity_" + _aux[i];
      params = _factory.getValidParams(auxkernel_type);
      params.set<std::vector<VariableName>>("pressure") = {_pressure};
      params.set<AuxVariableName>("variable") = _aux[i];
      params.set<MooseEnum>("component") = i;
      params.set<RealVectorValue>("gravity") = _gravity;
      _problem->addAuxKernel(auxkernel_type, auxkernel_name, params);
    }
  }

  if (_current_task == "add_bc")
  {
    // Constant concentration at top
    std::string bc_type = "DirichletBC";
    std::string bc_name = "concentration_top";
    InputParameters params = _factory.getValidParams(bc_type);
    params.set<NonlinearVariableName>("variable") = _concentration;
    params.set<std::vector<BoundaryName>>("boundary") = {"top"};
    params.set<Real>("value") = _boundary_concentration;
    _problem->addBoundaryCondition(bc_type, bc_name, params);
  }

  if (_current_task == "add_postprocessor")
  {
    // Boundary flux postprocessor
    std::string postprocessor_type = "NumbatSideFlux";
    std::string postprocessor_name = "boundary_flux";
    InputParameters params = _factory.getValidParams(postprocessor_type);
    params.set<std::vector<VariableName>>("variable") = {_concentration};
    params.set<std::vector<BoundaryName>>("boundary") = {"top"};
    params.set<ExecFlagEnum>("execute_on") = {EXEC_INITIAL, EXEC_TIMESTEP_END};
    _problem->addPostprocessor(postprocessor_type, postprocessor_name, params);

    // Mass postprocessor
    postprocessor_type = "NumbatTotalMass";
    postprocessor_name = "total_mass";
    params = _factory.getValidParams(postprocessor_type);
    params.set<std::vector<VariableName>>("variable") = {_concentration};
    params.set<ExecFlagEnum>("execute_on") = {EXEC_INITIAL, EXEC_TIMESTEP_END};
    _problem->addPostprocessor(postprocessor_type, postprocessor_name, params);
  }

  if (_current_task == "add_periodic_bc")
  {
    if (_periodic_bcs)
    {
      // Automatically add periodic boundary conditions
      std::vector<std::string> auto_dir;

      if (dim == 2)
        auto_dir = {"x"};

      if (dim == 3)
        auto_dir = {"x", "y"};

      // Set the parameters for AddPeriodicBCAction and add it
      const std::string type = "AddPeriodicBCAction";
      auto action_params = _action_factory.getValidParams(type);
      action_params.set<std::vector<std::string>>("auto_direction") = auto_dir;
      action_params.set<std::vector<VariableName>>("variable") = {_concentration, _pressure};
      // Create and add the action to the warehouse
      auto action = MooseSharedNamespace::static_pointer_cast<MooseObjectAction>(
          _action_factory.create(type, "AddPeriodicBCAction", action_params));
      _awh.addActionBlock(action);
    }
  }
}
