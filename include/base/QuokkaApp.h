#ifndef QUOKKAAPP_H
#define QUOKKAAPP_H

#include "MooseApp.h"

class QuokkaApp;

template<>
InputParameters validParams<QuokkaApp>();

class QuokkaApp : public MooseApp
{
public:
  QuokkaApp(const std::string & name, InputParameters parameters);
  virtual ~QuokkaApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* QUOKKAAPP_H */
