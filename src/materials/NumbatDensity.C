/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatDensity.h"

registerMooseObject("NumbatApp", NumbatDensity);

template <>
InputParameters
validParams<NumbatDensity>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("concentration", "The concentration variable");
  params.addRequiredParam<Real>("zero_density", "The density with zero concentration");
  params.addRequiredParam<Real>("delta_density",
                                "The density increase due to concentration at equilibrium");
  params.addRangeCheckedParam<Real>(
      "saturated_concentration",
      1.0,
      "saturated_concentration <= 1 & saturated_concentration > 0",
      "Concentration of species at full saturation. Note: should be equal "
      "to boundary condition concentration");
  params.addClassDescription(
      "This Material calculates the density of the fluid with given concentration");
  return params;
}

NumbatDensity::NumbatDensity(const InputParameters & parameters)
  : DerivativeMaterialInterface<Material>(parameters),
    _concentration(coupledValue("concentration")),
    _concentration_var(getVar("concentration", 0)->name()),
    _zero_density_input(getParam<Real>("zero_density")),
    _delta_density_input(getParam<Real>("delta_density")),
    _saturated_concentration(getParam<Real>("saturated_concentration")),
    _density(declareProperty<Real>("density")),
    _delta_density(declareProperty<Real>("delta_density"))
{
  if (coupledComponents("concentration") != 1)
    mooseError(_name, ": Only a single concentration species can be used");
  // Only one concentration species
  _ddensity_dc.resize(1);
  _ddensity_dc[0] = &declarePropertyDerivative<Real>("density", _concentration_var);
}

void
NumbatDensity::computeQpProperties()
{
  _density[_qp] =
      _zero_density_input + _concentration[_qp] * _delta_density_input / _saturated_concentration;
  _delta_density[_qp] = _delta_density_input;

  (*_ddensity_dc[0])[_qp] = _delta_density_input / _saturated_concentration;
}
