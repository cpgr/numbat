/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NumbatDiffusivity.h"

template <>
InputParameters
validParams<NumbatDiffusivity>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("diffusivity", "The diffusivity");
  params.addClassDescription("This Material provides a diffusivity material property");
  return params;
}

NumbatDiffusivity::NumbatDiffusivity(const InputParameters & parameters)
  : Material(parameters),
    _input_diffusivity(coupledValue("diffusivity")),
    _diffusivity(declareProperty<Real>("diffusivity"))
{
}

void
NumbatDiffusivity::computeQpProperties()
{
  _diffusivity[_qp] = _input_diffusivity[_qp];
}
