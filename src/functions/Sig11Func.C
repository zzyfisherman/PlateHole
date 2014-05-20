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

#include "Sig11Func.h"
#include <math.h>

template<>
InputParameters validParams<Sig11Func>()
{
  InputParameters params = validParams<Function>();
  params.addParam<Real>("M", 1.0, "Bending moment");
  params.addParam<Real>("I", 1.0, "Moment of inertia");
  return params;
}

Sig11Func::Sig11Func(const std::string & name, InputParameters parameters) :
    Function(name, parameters),
    _M(getParam<Real>("M")),
    _I(getParam<Real>("I"))
{}

Real
Sig11Func::value(Real t, const Point & p)
{
  Real tfac = (t < 1.0) ? 0.0 : (t-1.0);
  return tfac*(-_M*p(1)/_I);
}
