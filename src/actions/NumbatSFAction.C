/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatSFAction.h"
#include "FEProblem.h"
#include "AddVariableAction.h"
#include "MooseApp.h"
#include "MooseMesh.h"
#include "ActionWarehouse.h"
#include "ActionFactory.h"
#include "MooseObjectAction.h"
#include "MooseUtils.h"

#include "libmesh/string_to_enum.h"

registerMooseAction("NumbatApp", NumbatSFAction, "add_variable");
registerMooseAction("NumbatApp", NumbatSFAction, "add_aux_variable");
registerMooseAction("NumbatApp", NumbatSFAction, "add_kernel");
registerMooseAction("NumbatApp", NumbatSFAction, "add_bc");
registerMooseAction("NumbatApp", NumbatSFAction, "add_periodic_bc");
registerMooseAction("NumbatApp", NumbatSFAction, "add_postprocessor");

template <>
InputParameters
validParams<NumbatSFAction>()
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
  params.addParam<Real>("gamma", 1.0, "The anisotropy ratio");
  params.addParam<bool>("periodic_bcs", true, "Whether to add periodic boundary conditions");
  params.addClassDescription("Action to automatically add all variables, kernels, boundary "
                             "conditions and postprocessors for the dimensionless formulation");
  return params;
}

NumbatSFAction::NumbatSFAction(const InputParameters & parameters)
  : Action(parameters),
    _fe_type(Utility::string_to_enum<Order>(getParam<MooseEnum>("order")),
             Utility::string_to_enum<FEFamily>(getParam<MooseEnum>("family"))),
    _scaling(getParam<Real>("scaling")),
    _concentration("concentration"),
    _gamma(getParam<Real>("gamma")),
    _periodic_bcs(getParam<bool>("periodic_bcs"))
{
}

void
NumbatSFAction::act()
{
  const unsigned int dim = _mesh.get()->dimension();

  if (dim == 2)
  {
    _streamfunction = {"streamfunction"};
    _aux = {"u", "v"};
  }

  if (dim == 3)
  {
    _streamfunction = {"streamfunction_x", "streamfunction_y"};
    _aux = {"u", "v", "w"};
  }

  if (_current_task == "add_variable")
  {
    _problem->addVariable(_concentration, _fe_type, _scaling);

    for (auto sf : _streamfunction)
      _problem->addVariable(sf, _fe_type, _scaling);
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
    std::string kernel_type = "TimeDerivative";
    std::string kernel_name = "TimeDerivative";
    InputParameters params = _factory.getValidParams(kernel_type);
    params.set<NonlinearVariableName>("variable") = _concentration;
    _problem->addKernel(kernel_type, kernel_name, params);

    // Convection kernel for concentration
    kernel_type = "NumbatConvectionSF";
    kernel_name = "NumbatConvection";
    params = _factory.getValidParams(kernel_type);
    params.set<NonlinearVariableName>("variable") = _concentration;
    params.set<std::vector<VariableName>>("streamfunction") = _streamfunction;
    _problem->addKernel(kernel_type, kernel_name, params);

    // Diffusion kernel for concentration
    RealTensorValue anisotropic(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

    if (dim == 2)
      anisotropic(0, 0) *= _gamma;
    if (dim == 3)
    {
      anisotropic(0, 0) *= _gamma;
      anisotropic(1, 1) *= _gamma;
    }

    kernel_type = "NumbatDiffusionSF";
    kernel_name = "NumbatDiffusion";
    params = _factory.getValidParams(kernel_type);
    params.set<NonlinearVariableName>("variable") = _concentration;
    params.set<RealTensorValue>("anisotropic_tensor") = anisotropic;
    _problem->addKernel(kernel_type, kernel_name, params);

    // Darcy kernels for each streamfunction component
    for (unsigned int i = 0; i < _streamfunction.size(); ++i)
    {
      kernel_type = "NumbatDarcySF";
      kernel_name = "NumbatDarcy_" + _streamfunction[i];
      params = _factory.getValidParams(kernel_type);
      params.set<NonlinearVariableName>("variable") = _streamfunction[i];
      params.set<std::vector<VariableName>>("concentration") = {_concentration};
      params.set<MooseEnum>("component") = i;
      _problem->addKernel(kernel_type, kernel_name, params);
    }

    // AuxKernels for velocity components
    for (unsigned int i = 0; i < _aux.size(); ++i)
    {
      std::string auxkernel_type = "NumbatDarcyVelocitySF";
      std::string auxkernel_name = "NumbatDarcyVelocitySF_" + _aux[i];
      params = _factory.getValidParams(auxkernel_type);
      params.set<std::vector<VariableName>>("streamfunction") = _streamfunction;
      params.set<AuxVariableName>("variable") = _aux[i];
      params.set<MooseEnum>("component") = i;
      _problem->addAuxKernel(auxkernel_type, auxkernel_name, params);
    }
  }

  if (_current_task == "add_bc")
  {
    // Constant concentration at top
    std::string bc_type = "PresetBC";
    std::string bc_name = "concentration_top";
    InputParameters params = _factory.getValidParams(bc_type);
    params.set<NonlinearVariableName>("variable") = _concentration;
    params.set<std::vector<BoundaryName>>("boundary") = {"top"};
    params.set<Real>("value") = 1.0;
    _problem->addBoundaryCondition(bc_type, bc_name, params);

    // No-flow at the top and bottom for all streamfunctions
    for (auto sf : _streamfunction)
    {
      // Top boundary
      bc_type = "PresetBC";
      bc_name = sf + "_top";
      params = _factory.getValidParams(bc_type);
      params.set<NonlinearVariableName>("variable") = sf;
      params.set<std::vector<BoundaryName>>("boundary") = {"top"};
      params.set<Real>("value") = 0.0;
      _problem->addBoundaryCondition(bc_type, bc_name, params);

      // Bottom boundary
      bc_name = sf + "_bottom";
      params = _factory.getValidParams(bc_type);
      params.set<NonlinearVariableName>("variable") = sf;
      params.set<std::vector<BoundaryName>>("boundary") = {"bottom"};
      params.set<Real>("value") = 0.0;
      _problem->addBoundaryCondition(bc_type, bc_name, params);
    }
  }

  if (_current_task == "add_postprocessor")
  {
    // Boundary flux postprocessor
    std::string postprocessor_type = "NumbatSideFluxSF";
    std::string postprocessor_name = "boundary_flux";
    InputParameters params = _factory.getValidParams(postprocessor_type);
    params.set<std::vector<VariableName>>("variable") = {_concentration};
    params.set<std::vector<BoundaryName>>("boundary") = {"top"};
    params.set<ExecFlagEnum>("execute_on") = {EXEC_INITIAL, EXEC_TIMESTEP_END};
    _problem->addPostprocessor(postprocessor_type, postprocessor_name, params);

    // Mass postprocessor
    postprocessor_type = "NumbatTotalMassSF";
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
      std::vector<VariableName> vars{_concentration};

      if (dim == 2)
      {
        auto_dir = {"x"};
        vars.insert(vars.end(), _streamfunction.begin(), _streamfunction.end());
      }
      if (dim == 3)
      {
        auto_dir = {"x", "y"};
        vars.insert(vars.end(), _streamfunction.begin(), _streamfunction.end());
      }

      // Set the parameters for AddPeriodicBCAction and add it
      const std::string type = "AddPeriodicBCAction";
      auto action_params = _action_factory.getValidParams(type);
      action_params.set<std::vector<std::string>>("auto_direction") = auto_dir;
      action_params.set<std::vector<VariableName>>("variable") = vars;
      // Create and add the action to the warehouse
      auto action = MooseSharedNamespace::static_pointer_cast<MooseObjectAction>(
          _action_factory.create(type, "AddPeriodicBCAction", action_params));
      _awh.addActionBlock(action);
    }
  }
}
