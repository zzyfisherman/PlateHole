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

#ifndef SIG22FUNC_H
#define SIG22FUNC_H

#include "Function.h"

class Sig22Func;

template<>
InputParameters validParams<Sig22Func>();

class Sig22Func : public Function
{
public:
  Sig22Func(const std::string & name, InputParameters parameters);

  virtual Real value(Real t, const Point & p);

protected:
  Real _sig0;
  Real _a; // semi-major axis
  Real _b; // semi-minor axis
};

#endif //SIG11FUNC_H
