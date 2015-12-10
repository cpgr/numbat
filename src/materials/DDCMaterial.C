/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "DDCMaterial.h"

template<>
InputParameters validParams<DDCMaterial>()
{
  InputParameters params = validParams<Material>();

  params.addRequiredRangeCheckedParam<Real>("porosity", "0 <= porosity <= 1", "Porosity of the material (must be between 0 and 1)");
  params.addRequiredParam<RealTensorValue>("permeability", "The permeability tensor (m^2)");
  params.addRequiredParam<RealVectorValue>("gravity", "Gravitational acceleration vector downwards (m/s^2)");
  params.addRequiredParam<Real>("viscosity", "The fluid viscosity (Pa.s)");
  params.addRequiredParam<Real>("diffusivity", "The effective diffusivity (tortuosity x diffusion coefficient)");
  params.addRequiredParam<Real>("water_density", "The density of the resident fluid");
  params.addRequiredParam<Real>("solute_density", "The density of aqueous phase solute");
  params.addRequiredCoupledVar("pressure_variable", "The fluid pressure variable");
  params.addRequiredCoupledVar("solute_mass_fraction_variable", "The solute mass fraction variable");
  params.addCoupledVar("porosity_noise", 0.0, "The porosity noise AuxVariable");
  params.addCoupledVar("permeability_noise", 0.0, "The permeability noise AuxVariable");
  return params;
}

DDCMaterial::DDCMaterial(const InputParameters & parameters) :
  Material(parameters),

  _material_porosity(getParam<Real>("porosity")),
  _material_permeability(getParam<RealTensorValue>("permeability")),
  _material_gravity(getParam<RealVectorValue>("gravity")),
  _material_fluid_viscosity(getParam<Real>("viscosity")),
  _material_diffusivity(getParam<Real>("diffusivity")),
  _material_water_density(getParam<Real>("water_density")),
  _material_solute_density(getParam<Real>("solute_density")),

  _porosity(declareProperty<Real>("porosity")),
  _permeability(declareProperty<RealTensorValue>("permeability")),
  _gravity(declareProperty<RealVectorValue>("gravity")),
  _viscosity(declareProperty<Real>("viscosity")),
  _diffusivity(declareProperty<Real>("diffusivity")),
  _water_density(declareProperty<Real>("water_density")),
  _solute_density(declareProperty<Real>("solute_density")),
  _density(declareProperty<Real>("density")),
  _velocity(declareProperty<RealVectorValue>("velocity")),
  _ddensity_dx(declareProperty<Real>("ddensity_dx")),
  _dvelocity_dx(declareProperty<RealVectorValue>("dvelocity_dx")),
  _dvelocity_dp(declareProperty<RealTensorValue>("dvelocity_dp")),

  _grad_pressure(coupledGradient("pressure_variable")),
  _solute_mass_fraction(coupledValue("solute_mass_fraction_variable")),
  _porosity_noise(coupledValue("porosity_noise")),
  _permeability_noise(coupledValue("permeability_noise"))
{
}

void
DDCMaterial::computeQpProperties()
{
  /**
   * Set material properties at the quadrature points.
   * Porosity and/or permeability are scaled by a random
   * perturbation such that all values lie in the range
   * (x - y/2, x + y/2), where x is the given material value
   * and y is the amplitude of the noise
   */

  _porosity[_qp] = _material_porosity;
  if (isCoupled("porosity_noise"))
    _porosity[_qp] *= 1.0 + _porosity_noise[_qp];

  _permeability[_qp] = _material_permeability;
    if (isCoupled("permeability_noise"))
      _permeability[_qp] *= 1.0 + _permeability_noise[_qp];

  _gravity[_qp] = _material_gravity;
  _viscosity[_qp] = _material_fluid_viscosity;
  _diffusivity[_qp] = _material_diffusivity;
  _water_density[_qp] = _material_water_density;
  _solute_density[_qp] = _material_solute_density;

  /// Calculate the fluid density
  _density[_qp] = 1.0 / (_solute_mass_fraction[_qp] / _solute_density[_qp] +
    (1.0 - _solute_mass_fraction[_qp]) / _water_density[_qp]);

  /// Calculate the velocity using Darcy's law
  _velocity[_qp] = - _permeability[_qp] / _viscosity[_qp] * (_grad_pressure[_qp] - _density[_qp] * _gravity[_qp]);

  /// Jacobians require the derivative of density wrt solute mass fraction
  _ddensity_dx[_qp] = (1.0 / _water_density[_qp] - 1.0 / _solute_density[_qp]) * _density[_qp] * _density[_qp];

  /// Jacobians require the derivative of the Darcy velocity wrt solute mass fraction
  _dvelocity_dx[_qp] = _permeability[_qp] * _ddensity_dx[_qp] * _gravity[_qp] / _viscosity[_qp];

  /// Jacobians require the derivative of the Darcy velocity wrt pressure
  _dvelocity_dp[_qp] = - _permeability[_qp] / _viscosity[_qp];
}
