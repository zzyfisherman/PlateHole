#include "PlateholeApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

// PlateHole include
#include "Sig11Func.h"
#include "Sig12Func.h"
#include "Sig22Func.h"
#include "Disp1Func.h"
#include "Disp2Func.h"

template<>
InputParameters validParams<PlateholeApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

PlateholeApp::PlateholeApp(InputParameters parameters) :
    MooseApp(parameters)
{

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

extern "C" void PlateholeApp__registerApps() { PlateholeApp::registerApps(); }
void
PlateholeApp::registerApps()
{
  registerApp(PlateholeApp);
}

void
PlateholeApp::registerObjects(Factory & factory)
{
  registerFunction(Sig11Func); // register ZZY function
  registerFunction(Sig12Func); // register ZZY function
  registerFunction(Sig22Func); // register ZZY function
  registerFunction(Disp1Func);
  registerFunction(Disp2Func);
}

void
PlateholeApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
