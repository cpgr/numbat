/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "RandomNoiseAux.h"

template<>
InputParameters validParams<RandomNoiseAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRangeCheckedParam<Real>("noise_amplitude", 0.0, "0 <= noise_amplitude <= 1", "The amplitude of the random noise");
  return params;
}

RandomNoiseAux::RandomNoiseAux(const InputParameters & parameters) :
    AuxKernel(parameters),
    _noise_amplitude(getParam<Real>("noise_amplitude"))
{
  setRandomResetFrequency(EXEC_INITIAL);

  /**
   * Note that as this random noise applies to material properties, the
   * AuxVariable must be elemental
   */
  if (isNodal())
    mooseError("Can't use RandomNoiseAux with a nodal AuxVariable");
}

Real
RandomNoiseAux::computeValue()
{
  return _noise_amplitude * (getRandomReal() - 0.5);
}
