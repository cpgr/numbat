#include "NumbatApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

/// Aux kernels
#include "VelocityDDCAux.h"
#include "RandomNoiseAux.h"

/// Initial conditions
#include "PerturbationIC.h"

/// Kernels
#include "DarcyDDC.h"
#include "ConvectionDiffusionDDC.h"
#include "DDCDarcyFlux.h"
#include "DDCDiffusion.h"

/// Mesh modifiers
#include "VerticalRefine.h"

/// Materials
#include "DDCMaterial.h"

template<>
InputParameters validParams<NumbatApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

NumbatApp::NumbatApp(InputParameters parameters) :
    MooseApp(parameters)
{

  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  NumbatApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  NumbatApp::associateSyntax(_syntax, _action_factory);
}

NumbatApp::~NumbatApp()
{
}

// External entry point for dynamic application loading
extern "C" void NumbatApp__registerApps() { NumbatApp::registerApps(); }
void
NumbatApp::registerApps()
{
  registerApp(NumbatApp);
}

// External entry point for dynamic object registration
extern "C" void NumbatApp__registerObjects(Factory & factory) { NumbatApp::registerObjects(factory); }
void
NumbatApp::registerObjects(Factory & factory)
{
  // Register the auxillary kernels
  registerAux(VelocityDDCAux);
  registerAux(RandomNoiseAux);

  // Register initial conditions
  registerInitialCondition(PerturbationIC);

  // Register the kernels
  registerKernel(DarcyDDC);
  registerKernel(ConvectionDiffusionDDC);
  registerKernel(DDCDarcyFlux);
  registerKernel(DDCDiffusion);

  // Register the mesh modifiers
  registerMeshModifier(VerticalRefine);

  // Regiseter the material
  registerMaterial(DDCMaterial);
}

// External entry point for dynamic syntax association
extern "C" void NumbatApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { NumbatApp::associateSyntax(syntax, action_factory); }
void
NumbatApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
