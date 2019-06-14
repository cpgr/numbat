/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatDensityMultipleSpecies.h"

registerMooseObject("NumbatApp", NumbatDensityMultipleSpecies);

template <>
InputParameters
validParams<NumbatDensityMultipleSpecies>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("concentration", "The concentration variable");
  params.addRequiredCoupledVar("coefficient", "The coefficient for each concentration variable");
  params.addRequiredParam<Real>("unsaturated_density", "The density with zero concentration");
  params.addRequiredParam<std::vector<Real>>("saturated_concentration",
                                             "The saturated concentration");
  params.addClassDescription(
      "This Material calculates the density of the fluid with given species concentration(s)");
  return params;
}

NumbatDensityMultipleSpecies::NumbatDensityMultipleSpecies(const InputParameters & parameters)
  : DerivativeMaterialInterface<Material>(parameters),
    _num_species(coupledComponents("concentration")),
    _concentration(_num_species),
    _concentration_var(_num_species),
    _saturated_concentration(getParam<std::vector<Real>>("saturated_concentration")),
    _coefficients(_num_species),
    _unsaturated_density(getParam<Real>("unsaturated_density")),
    _density(declareProperty<Real>("density")),
    _delta_density(declareProperty<Real>("delta_density")),
    _ddensity_dc(_num_species)
{
  for (unsigned int i = 0; i < _num_species; ++i)
  {
    _concentration[i] = &coupledValue("concentration", i);
    _concentration_var[i] = getVar("concentration", i)->name();
    _coefficients[i] = &coupledValue("coefficient", i);
    _ddensity_dc[i] = &declarePropertyDerivative<Real>("density", _concentration_var[i]);
  }
}

void
NumbatDensityMultipleSpecies::computeQpProperties()
{
  _density[_qp] = 1.0;
  _delta_density[_qp] = 0.0;

  for (unsigned int i = 0; i < _num_species; ++i)
  {
    _density[_qp] += (*_coefficients[i])[_qp] * (*_concentration[i])[_qp];
    _delta_density[_qp] += (*_coefficients[i])[_qp] * _saturated_concentration[i];
    (*_ddensity_dc[i])[_qp] = _unsaturated_density * (*_coefficients[i])[_qp];
  }

  _density[_qp] *= _unsaturated_density;
  _delta_density[_qp] *= _unsaturated_density;
}
