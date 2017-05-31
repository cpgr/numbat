/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NumbatPorosity.h"

template <>
InputParameters
validParams<NumbatPorosity>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("porosity", "The porosity");
  params.addRangeCheckedParam<Real>(
      "amplitude", 0, "amplitude >= 0 & amplitude <= 1", "Amplitude of the random perturbation");
  params.addClassDescription("This Material provides a porosity material property");
  return params;
}

NumbatPorosity::NumbatPorosity(const InputParameters & parameters)
  : Material(parameters),
    _input_porosity(coupledValue("porosity")),
    _porosity(declareProperty<Real>("porosity")),
    _amplitude(getParam<Real>("amplitude"))
{
  // The random numbers must be sampled from the same set every linear iteration
  setRandomResetFrequency(EXEC_LINEAR);
}

void
NumbatPorosity::computeQpProperties()
{
  Real rand = -1.0 + 2.0 * getRandomReal();
  _porosity[_qp] = _input_porosity[_qp] * (1.0 + _amplitude * rand);
}
