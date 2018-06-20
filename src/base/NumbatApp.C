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

template <>
InputParameters
validParams<NumbatApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

registerKnownLabel("NumbatApp");

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

void
NumbatApp::registerApps()
{
  registerApp(NumbatApp);
}

void
NumbatApp::registerObjects(Factory & factory)
{
  Registry::registerObjectsTo(factory, {"NumbatApp"});
}

void
NumbatApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"NumbatApp"});

  registerSyntax("NumbatSFAction", "Numbat/Dimensionless");
}

/// External entry point for dynamic application loading
extern "C" void
NumbatApp__registerApps()
{
  NumbatApp::registerApps();
}

/// External entry point for dynamic object registration
extern "C" void
NumbatApp__registerObjects(Factory & factory)
{
  NumbatApp::registerObjects(factory);
}

/// External entry point for dynamic syntax association
extern "C" void
NumbatApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  NumbatApp::associateSyntax(syntax, action_factory);
}
