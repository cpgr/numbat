#include "NumbatApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

// Aux kernels
#include "VelocityAux.h"

// Initial conditions
#include "PerturbationIC.h"

// Kernels
#include "TwoDDarcyDDC.h"
#include "ThreeDDarcyDDCx.h"
#include "ThreeDDarcyDDCy.h"
#include "TwoDConvectionDiffusionDDC.h"
#include "ThreeDConvectionDiffusionDDC.h"

// Mesh modifiers
#include "VerticalRefine.h"

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
  srand(processor_id());

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
#undef  registerApp
#define registerApp(name) AppFactory::instance().reg<name>(#name)
  registerApp(NumbatApp);
#undef  registerApp
#define registerApp(name) AppFactory::instance().regLegacy<name>(#name)
}

// External entry point for dynamic object registration
extern "C" void NumbatApp__registerObjects(Factory & factory) { NumbatApp::registerObjects(factory); }
void
NumbatApp::registerObjects(Factory & factory)
{
#undef registerObject
#define registerObject(name) factory.reg<name>(stringifyName(name))
  // Register the auxillary kernels
  registerAux(VelocityAux);

  // Register initial conditions
  registerInitialCondition(PerturbationIC);

  // Register the kernels
  registerKernel(TwoDDarcyDDC);
  registerKernel(TwoDConvectionDiffusionDDC);
  registerKernel(ThreeDDarcyDDCx);
  registerKernel(ThreeDDarcyDDCy);
  registerKernel(ThreeDConvectionDiffusionDDC);

  // Register the mesh modifiers
  registerMeshModifier(VerticalRefine);
#undef registerObject
#define registerObject(name) factory.regLegacy<name>(stringifyName(name))
}

// External entry point for dynamic syntax association
extern "C" void NumbatApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { NumbatApp::associateSyntax(syntax, action_factory); }
void
NumbatApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
#undef registerAction
#define registerAction(tplt, action) action_factory.reg<tplt>(stringifyName(tplt), action)

#undef registerAction
#define registerAction(tplt, action) action_factory.regLegacy<tplt>(stringifyName(tplt), action)
}
