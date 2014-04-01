#ifndef PLATEHOLEAPP_H
#define PLATEHOLEAPP_H

#include "MooseApp.h"

class PlateholeApp;

template<>
InputParameters validParams<PlateholeApp>();

class PlateholeApp : public MooseApp
{
public:
  PlateholeApp(const std::string & name, InputParameters parameters);
  virtual ~PlateholeApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* PLATEHOLEAPP_H */
