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

#include "Disp2Func.h"
#include <math.h>

template<>
InputParameters validParams<Disp2Func>()
{
  InputParameters params = validParams<Function>();
  params.addParam<Real>("M", 1.0, "Bending moment");
  params.addParam<Real>("E", 1.0, "Young's modulus");
  params.addParam<Real>("I", 1.0, "Moment of inertia");
  params.addParam<Real>("l", 1.0, "Beam length");
  params.addParam<Real>("nu", 1.0, "Poisson ratio");
  return params;
}

Disp2Func::Disp2Func(const std::string & name, InputParameters parameters) :
    Function(name, parameters),
    _M(getParam<Real>("M")),
    _E(getParam<Real>("E")),
    _I(getParam<Real>("I")),
    _l(getParam<Real>("l")),
    _nu(getParam<Real>("nu"))
{}

Real
Disp2Func::value(Real t, const Point & p)
{
  Real tfac = (t < 1.0) ? 0.0 : (t-1.0);
  return tfac*(_M/(2*_E*_I))*(1-_nu*_nu)*(p(0)*p(0)-0.25*_l*_l);
}
