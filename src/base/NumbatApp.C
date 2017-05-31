#include "NumbatApp.h"
#include "Moose.h"
#include "AppFactory.h"
//#include "ModulesApp.h"
#include "MooseSyntax.h"

/// App revision
#include "NumbatRevision.h"

/// Aux kernels
#include "VelocityDDCAux.h"
#include "DarcyVelocityAux.h"

/// Boundary conditions
#include "NumbatPerturbationBC.h"

/// Initial conditions
#include "PerturbationIC.h"

/// Kernels
#include "DarcyDDC.h"
#include "ConvectionDiffusionDDC.h"
#include "NumbatDiffusion.h"
#include "NumbatTimeDerivative.h"
#include "NumbatDarcy.h"
#include "NumbatConvection.h"

/// Materials
#include "NumbatPorosity.h"
#include "NumbatPermeability.h"
#include "NumbatPermeabilityFromVar.h"
#include "NumbatDiffusivity.h"
#include "NumbatDensity.h"
#include "NumbatViscosity.h"

/// Mesh modifiers
#include "VerticalRefine.h"

template <>
InputParameters
validParams<NumbatApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

NumbatApp::NumbatApp(InputParameters parameters) : MooseApp(parameters)
{
  /**
   * Print the git revision information to the console
   */
  _console << std::left << "App Information: \n";
  _console << std::setw(25) << "Numbat version: " << NUMBAT_REVISION << "\n"
           << "\n";

  Moose::registerObjects(_factory);
  // ModulesApp::registerObjects(_factory);
  NumbatApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  // ModulesApp::associateSyntax(_syntax, _action_factory);
  NumbatApp::associateSyntax(_syntax, _action_factory);
}

NumbatApp::~NumbatApp() {}

/// External entry point for dynamic application loading
extern "C" void
NumbatApp__registerApps()
{
  NumbatApp::registerApps();
}
void
NumbatApp::registerApps()
{
  registerApp(NumbatApp);
}

/// External entry point for dynamic object registration
extern "C" void
NumbatApp__registerObjects(Factory & factory)
{
  NumbatApp::registerObjects(factory);
}
void
NumbatApp::registerObjects(Factory & factory)
{
  /// Register the auxillary kernels
  registerAux(VelocityDDCAux);
  registerAux(DarcyVelocityAux);

  /// Register the boundary conditions
  registerBoundaryCondition(NumbatPerturbationBC);

  /// Register initial conditions
  registerInitialCondition(PerturbationIC);

  /// Register the kernels
  registerKernel(DarcyDDC);
  registerKernel(ConvectionDiffusionDDC);
  registerKernel(NumbatDiffusion);
  registerKernel(NumbatTimeDerivative);
  registerKernel(NumbatDarcy);
  registerKernel(NumbatConvection);

  // Register the Materials
  registerMaterial(NumbatPorosity);
  registerMaterial(NumbatPermeability);
  registerMaterial(NumbatPermeabilityFromVar);
  registerMaterial(NumbatDiffusivity);
  registerMaterial(NumbatDensity);
  registerMaterial(NumbatViscosity);

  /// Register the mesh modifiers
  registerMeshModifier(VerticalRefine);
}

/// External entry point for dynamic syntax association
extern "C" void
NumbatApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  NumbatApp::associateSyntax(syntax, action_factory);
}
void
NumbatApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
