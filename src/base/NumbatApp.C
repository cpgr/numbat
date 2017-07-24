/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatApp.h"
#include "Moose.h"
#include "AppFactory.h"
//#include "ModulesApp.h"
#include "MooseSyntax.h"

// App revision
#include "NumbatRevision.h"

// Aux kernels
#include "NumbatDarcyVelocitySF.h"
#include "NumbatDarcyVelocity.h"

// Boundary conditions
#include "NumbatPerturbationBC.h"

// Initial conditions
#include "NumbatPerturbationIC.h"

// Kernels
#include "NumbatTimeDerivative.h"
#include "NumbatDarcy.h"
#include "NumbatDarcySF.h"
#include "NumbatConvection.h"
#include "NumbatConvectionSF.h"
#include "NumbatDiffusion.h"
#include "NumbatDiffusionSF.h"

// Materials
#include "NumbatPorosity.h"
#include "NumbatPermeability.h"
#include "NumbatPermeabilityFromVar.h"
#include "NumbatDiffusivity.h"
#include "NumbatDensity.h"
#include "NumbatViscosity.h"

// MeshModifier
#include "NumbatBiasedMesh.h"

// Postprocessors
#include "NumbatRayleighNumber.h"
#include "NumbatSideFlux.h"
#include "NumbatSideFluxSF.h"
#include "NumbatTotalMass.h"
#include "NumbatTotalMassSF.h"

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
  // Print the git revision information to the console
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
  registerAux(NumbatDarcyVelocitySF);
  registerAux(NumbatDarcyVelocity);

  /// Register the boundary conditions
  registerBoundaryCondition(NumbatPerturbationBC);

  /// Register initial conditions
  registerInitialCondition(NumbatPerturbationIC);

  /// Register the kernels
  registerKernel(NumbatTimeDerivative);
  registerKernel(NumbatDarcy);
  registerKernel(NumbatDarcySF);
  registerKernel(NumbatConvection);
  registerKernel(NumbatConvectionSF);
  registerKernel(NumbatDiffusion);
  registerKernel(NumbatDiffusionSF);

  // Register the Materials
  registerMaterial(NumbatPorosity);
  registerMaterial(NumbatPermeability);
  registerMaterial(NumbatPermeabilityFromVar);
  registerMaterial(NumbatDiffusivity);
  registerMaterial(NumbatDensity);
  registerMaterial(NumbatViscosity);

  // Register the MeshModifiers
  registerMeshModifier(NumbatBiasedMesh);

  /// Register the Postprocessors
  registerPostprocessor(NumbatRayleighNumber);
  registerPostprocessor(NumbatSideFlux);
  registerPostprocessor(NumbatSideFluxSF);
  registerPostprocessor(NumbatTotalMass);
  registerPostprocessor(NumbatTotalMassSF);
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
