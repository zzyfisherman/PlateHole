#ifndef HYPERB_H
#define HYPERB_H

#include <cmath>
#include <iostream>
#include <complex>

static std::complex<double> cacosh(const std::complex<double> z)
{
  return log(z + sqrt(z*z - 1.0));
}

static std::complex<double> casinh(const std::complex<double> z)
{
  return log(z + sqrt(z*z + 1.0));
}

#endif
