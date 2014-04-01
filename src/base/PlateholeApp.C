#include "PlateholeApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

template<>
InputParameters validParams<PlateholeApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

PlateholeApp::PlateholeApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(libMesh::processor_id());
  
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  PlateholeApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  PlateholeApp::associateSyntax(_syntax, _action_factory);
}

PlateholeApp::~PlateholeApp()
{
}

void
PlateholeApp::registerApps()
{
  registerApp(PlateholeApp);
}

void
PlateholeApp::registerObjects(Factory & factory)
{
}

void
PlateholeApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
