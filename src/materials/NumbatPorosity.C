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
  params.addRequiredCoupledVar("porosity", "The porosity (can be either a variable or a value)");
  params.addCoupledVar("noise", 0, "Variable with random noise to add to porosity");
  params.addClassDescription("This Material provides a porosity material property");
  return params;
}

NumbatPorosity::NumbatPorosity(const InputParameters & parameters)
  : Material(parameters),
    _input_porosity(coupledValue("porosity")),
    _porosity(declareProperty<Real>("porosity")),
    _random_noise(coupledValue("noise"))
{
}

void
NumbatPorosity::computeQpProperties()
{
  _porosity[_qp] = _input_porosity[_qp] + _random_noise[_qp];
}
