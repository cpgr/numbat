/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NumbatPerturbationBC.h"

template <>
InputParameters
validParams<NumbatPerturbationBC>()
{
  InputParameters params = validParams<PresetBC>();
  params.addRequiredParam<Real>("value", "Average value of the boundary condition");
  params.addRequiredParam<Real>("amplitude", "Amplitude of the random perturbation");
  params.addClassDescription("Dirichlet boundary condition that includes a random perturbation");
  return params;
}

NumbatPerturbationBC::NumbatPerturbationBC(const InputParameters & parameters)
  : PresetBC(parameters), _value(getParam<Real>("value")), _amplitude(getParam<Real>("amplitude"))
{
  // Amplitude must be less than value
  if (_amplitude > _value)
    mooseError("Amplitude of perturbation must be less than average value in ", _name);

  // The random numbers must be sampled from the same set every linear iteration
  setRandomResetFrequency(EXEC_LINEAR);
}

Real
NumbatPerturbationBC::computeQpValue()
{
  // The BC is the value minus a random number between 0 and amplitude
  return _value - _amplitude * getRandomReal();
}
