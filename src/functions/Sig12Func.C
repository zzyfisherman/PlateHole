/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "Sig12Func.h"
#include <math.h>

template<>
InputParameters validParams<Sig12Func>()
{
  InputParameters params = validParams<Function>();
  params.addParam<Real>("sig0", 1.0, "The value of tensile traction in x");
  params.addParam<Real>("a", 1.0, "The radius of the hole");
  return params;
}

Sig12Func::Sig12Func(const std::string & name, InputParameters parameters) :
    Function(name, parameters),
    _sig0(getParam<Real>("sig0")),
    _a(getParam<Real>("a"))
{}

Real
Sig12Func::value(Real /*t*/, const Point & p)
{
  double r = 1.0;
  double theta = 1.0;
//  return _alpha*_alpha*libMesh::pi*libMesh::pi*std::sin(_alpha*libMesh::pi*p(0));  // p(0) == x
  r = sqrt(p(0)*p(0) + p(1)*p(1));
  theta = atan2(p(1),p(0));
  return _sig0*(-0.5*(_a/r)*(_a/r)*(sin(2.0*theta)+sin(4.0*theta)) + 1.5*pow((_a/r),4)*sin(4.0*theta));
}
