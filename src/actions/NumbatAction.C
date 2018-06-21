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

template <>
InputParameters
validParams<NumbatAction>()
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
  params.addParam<Real>(
      "boundary_concentration", 1, "Concentration at constant-concentration boundary");
  params.addClassDescription("Action to automatically add all variables, kernels, boundary "
                             "conditions and postprocessors for the dimensional formulation");
  return params;
}

NumbatAction::NumbatAction(const InputParameters & parameters)
  : Action(parameters),
    _fe_type(Utility::string_to_enum<Order>(getParam<MooseEnum>("order")),
             Utility::string_to_enum<FEFamily>(getParam<MooseEnum>("family"))),
    _scaling(getParam<Real>("scaling")),
    _concentration("concentration"),
    _pressure("pressure"),
    _boundary_concentration(getParam<Real>("boundary_concentration"))
{
}

void
NumbatAction::act()
{
  const unsigned int dim = _mesh.get()->dimension();

  if (dim == 2)
    _aux = {"u", "v"};

  if (dim == 3)
    _aux = {"u", "v", "w"};

  if (_current_task == "add_variable")
  {
    _problem->addVariable(_concentration, _fe_type, _scaling);
    _problem->addVariable(_pressure, _fe_type, _scaling);
  }

  if (_current_task == "add_aux_variable")
  {
    const FEType _aux_fe_type(Utility::string_to_enum<Order>("constant"),
                              Utility::string_to_enum<FEFamily>("monomial"));

    for (auto auxvar : _aux)
      _problem->addAuxVariable(auxvar, _aux_fe_type);
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
    _problem->addPostprocessor(postprocessor_type, postprocessor_name, params);

    // Mass postprocessor
    postprocessor_type = "NumbatTotalMass";
    postprocessor_name = "total_mass";
    params = _factory.getValidParams(postprocessor_type);
    params.set<std::vector<VariableName>>("variable") = {_concentration};
    _problem->addPostprocessor(postprocessor_type, postprocessor_name, params);
  }

  if (_current_task == "add_periodic_bc")
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
