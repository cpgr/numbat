/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

// App revision
#include "NumbatRevision.h"

InputParameters
NumbatApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  return params;
}

registerKnownLabel("NumbatApp");

NumbatApp::NumbatApp(InputParameters parameters) : MooseApp(parameters)
{
  // Print the git revision information to the console
  _console << std::left << "App Information: \n";
  _console << std::setw(25) << "Numbat version: " << NUMBAT_REVISION << "\n"
           << "\n";

  NumbatApp::registerAll(_factory, _action_factory, _syntax);
}

NumbatApp::~NumbatApp() {}

void
NumbatApp::registerApps()
{
  registerApp(NumbatApp);
}

void
NumbatApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"NumbatApp"});

  registerSyntax("NumbatAction", "Numbat/Dimensional");
  registerSyntax("NumbatSFAction", "Numbat/Dimensionless");
  registerSyntax("NumbatEffectivePermeabilityAction", "Numbat/EffectivePermeability");
}

// External entry point for dynamic application loading
extern "C" void
NumbatApp__registerApps()
{
  NumbatApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
NumbatApp__registerAll(Factory & factory, ActionFactory & action_factory, Syntax & syntax)
{
  NumbatApp::registerAll(factory, action_factory, syntax);
}

void
NumbatApp::registerAll(Factory & factory, ActionFactory & action_factory, Syntax & syntax)
{
  Registry::registerObjectsTo(factory, {"NumbatApp"});
  NumbatApp::associateSyntax(syntax, action_factory);

  Moose::registerAll(factory, action_factory, syntax);
}
