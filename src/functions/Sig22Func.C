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

#include "Sig22Func.h"
#include <math.h>

template<>
InputParameters validParams<Sig22Func>()
{
  InputParameters params = validParams<Function>();
  params.addParam<Real>("sig0", 1.0, "The value of tensile traction in x");
  params.addParam<Real>("a", 1.0, "The radius of the hole");
  return params;
}

Sig22Func::Sig22Func(const InputParameters & parameters) :
    Function(parameters),
    _sig0(getParam<Real>("sig0")),
    _a(getParam<Real>("a"))
{}

Real
Sig22Func::value(Real t, const Point & p)
{
  Real r = 0.0;
  Real theta = 0.0;
  Real val = 0.0;
  Real tfac = (t < 1.0) ? 0.0 : (t-1.0);

  r = sqrt(p(0)*p(0) + p(1)*p(1));
  theta = atan2(p(1),p(0));
  if (r != 0.0)
    val = tfac*_sig0*(-(_a/r)*(_a/r)*(0.5*cos(2.0*theta)-cos(4.0*theta)) - 1.5*pow((_a/r),4)*cos(4.0*theta));

  return val;
}
