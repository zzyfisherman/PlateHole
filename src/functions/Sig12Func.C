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
#include <complex>
#include "hyperb.h"

template<>
InputParameters validParams<Sig12Func>()
{
  InputParameters params = validParams<Function>();
  params.addParam<Real>("sig0", 1.0, "The value of tensile traction in x");
  params.addParam<Real>("a", 1.0, "Semi-major axis of the elliptic hole");
  params.addParam<Real>("b", 1.0, "Semi-minor axis of the elliptic hole");
  return params;
}

Sig12Func::Sig12Func(const std::string & name, InputParameters parameters) :
    Function(name, parameters),
    _sig0(getParam<Real>("sig0")),
    _a(getParam<Real>("a")),
    _b(getParam<Real>("b"))
{}

Real
Sig12Func::value(Real t, const Point & p)
{
  Real c = 0.0; // focus
  Real ksi0 = 0.0;
  std::complex<double> z(p(1),p(0)); // NOTE: x & y are flipped over here
  std::complex<double> z_bar = conj(z);
  std::complex<double> zeta(0.0,0.0);
  std::complex<double> phipp(0.0,0.0); // 2nd derivative of phi(z)
  std::complex<double> chipp(0.0,0.0); // 2nd derivative of chi(z)
  Real val = 0.0;
  Real tfac = (t < 1.0) ? 0.0 : (t-1.0);

  c = sqrt(_a*_a - _b*_b); // focus
  ksi0 = acosh(_a/c); // see Timoshenko P 187
  zeta = cacosh((1.0/c)*z); // curviliear coords of (x,y)
  phipp = (-0.25*_sig0/c)*(1+exp(2*ksi0))*(1.0/(sinh(zeta)*sinh(zeta)*sinh(zeta)));
  chipp = (0.25*_sig0)*(2.0*exp(2.0*ksi0)*cosh(2.0*zeta-2.0*ksi0)
        + (cosh(2.0*ksi0)+1.0-exp(2.0*ksi0)*sinh(2.0*zeta-2.0*ksi0))*(1.0/tanh(zeta)))/(sinh(zeta)*sinh(zeta));

  if (real(zeta) != 0.0)
    val = tfac*imag(z_bar*phipp + chipp);//sig_xy in Timoshenko

  return val;
}
