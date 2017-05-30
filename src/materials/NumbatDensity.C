/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NumbatDensity.h"

template <>
InputParameters
validParams<NumbatDensity>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("concentration", "The concentration variable");
  params.addRequiredParam<Real>("zero_density", "The density with zero concentration");
  params.addRequiredParam<Real>("delta_density",
                                "The density increase due to concentration at equilibrium");
  params.addClassDescription(
      "This Material calculates the density of the fluid with given concentration");
  return params;
}

NumbatDensity::NumbatDensity(const InputParameters & parameters)
  : DerivativeMaterialInterface<Material>(parameters),
    _concentration(coupledValue("concentration")),
    _concentration_name(getVar("concentration", 0)->name()),
    _zero_density(getParam<Real>("zero_density")),
    _delta_density(getParam<Real>("delta_density")),
    _density(declareProperty<Real>("density")),
    _ddensity_dc(declarePropertyDerivative<Real>("density", _concentration_name))
{
}

void
NumbatDensity::computeQpProperties()
{
  _density[_qp] = _zero_density + _concentration[_qp] * _delta_density;
  _ddensity_dc[_qp] = _delta_density;
}
