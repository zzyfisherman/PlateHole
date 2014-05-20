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
#include <complex>
#include "hyperb.h"

template<>
InputParameters validParams<Disp2Func>()
{
  InputParameters params = validParams<Function>();
  params.addParam<Real>("sig0", 1.0, "The value of tensile traction in x");
  params.addParam<Real>("a", 1.0, "Semi-major axis of the elliptic hole");
  params.addParam<Real>("b", 1.0, "Semi-minor axis of the elliptic hole");
  params.addParam<Real>("E", 1.0, "Young's modulus");
  params.addParam<Real>("nu", 1.0, "Poission ratio");
  return params;
}

Disp2Func::Disp2Func(const std::string & name, InputParameters parameters) :
    Function(name, parameters),
    _sig0(getParam<Real>("sig0")),
    _a(getParam<Real>("a")),
    _b(getParam<Real>("b")),
    _E(getParam<Real>("E")),
    _nu(getParam<Real>("nu"))
{}

Real
Disp2Func::value(Real /*t*/, const Point & p)
{
  Real c = 0.0; // focus
  Real mu = 0.0; // Shear modulus
  Real disp2 = 0.0;
  Real nu_bar = 0.0; // the poission ratio for plain strain
  Real ksi0 = 0.0;
  std::complex<double> z(p(1),p(0)); // NOTE: x & y are flipped over here
  std::complex<double> zeta(0.0,0.0);
  std::complex<double> zeta_bar(0.0,0.0); // conjugate of zeta
  std::complex<double> phi(0.0,0.0);
  std::complex<double> phip_bar(0.0,0.0);
  std::complex<double> chip_bar(0.0,0.0);

  c = sqrt(_a*_a - _b*_b); // focus
  nu_bar = _nu/(1.0 - _nu); // for plain strain
  mu = 0.5*_E/(1+_nu); // shear modulus
  ksi0 = acosh(_a/c); // see Timoshenko P 187
  zeta = cacosh((1.0/c)*z); // curviliear coords of (x,y)
  zeta_bar = conj(zeta);
  phi = (0.25*_sig0*c)*(-exp(2.0*ksi0)*cosh(zeta) + (1.0+exp(2.0*ksi0))*sinh(zeta));
  phip_bar = (0.25*_sig0)*(-exp(2.0*ksi0) + (1.0+exp(2.0*ksi0))*(1.0/tanh(zeta_bar)));
  chip_bar = (-0.25*_sig0*c)*(1.0/sinh(zeta_bar))*(cosh(2.0*ksi0) + 1.0 - exp(2.0*ksi0)*sinh(2.0*zeta_bar-2.0*ksi0));

  if (real(zeta) < ksi0) // inside the elliptic hole
    disp2 = 0.0;
  else
  {
    disp2 = real((0.5/mu)*((3.0-nu_bar)/(1.0+nu_bar)*phi - z*phip_bar - chip_bar));//disp_x in Timoshenko
  }

  return disp2;
}
