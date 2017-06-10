/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATAPP_H
#define NUMBATAPP_H

#include "MooseApp.h"

class NumbatApp;

template <>
InputParameters validParams<NumbatApp>();

class NumbatApp : public MooseApp
{
public:
  NumbatApp(InputParameters parameters);
  virtual ~NumbatApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* NUMBATAPP_H */
