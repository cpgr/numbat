/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef RANDOMNOISEAUX_H
#define RANDOMNOISEAUX_H

#include "AuxKernel.h"

class RandomNoiseAux;

template<>
InputParameters validParams<RandomNoiseAux>();

class RandomNoiseAux : public AuxKernel
{
public:

  RandomNoiseAux(const InputParameters & parameters);

protected:

  virtual Real computeValue();

private:
  /// Random noise amplitude
  Real _noise_amplitude;
};

#endif //RANDOMNOISEAUX_H
