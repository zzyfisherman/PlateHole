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

#ifndef DISP1FUNC_H
#define DISP1FUNC_H

#include "Function.h"

class Disp1Func;

template<>
InputParameters validParams<Disp1Func>();

class Disp1Func : public Function
{
public:
  Disp1Func(const std::string & name, InputParameters parameters);

  virtual Real value(Real t, const Point & p);

protected:
  Real _sig0;
  Real _a; // hole radius
  Real _E; // young's modulus
  Real _nu; // possion ratio
};

#endif //DISP1FUNC_H
