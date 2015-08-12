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

#ifndef DISP2FUNC_H
#define DISP2FUNC_H

#include "Function.h"

class Disp2Func;

template<>
InputParameters validParams<Disp2Func>();

class Disp2Func : public Function
{
public:
  Disp2Func(const InputParameters & parameters);

  virtual Real value(Real t, const Point & p);

protected:
  Real _sig0;
  Real _a; // hole radius
  Real _E; // young's modulus
  Real _nu; // poission ratio
};

#endif //DISP2FUNC_H
