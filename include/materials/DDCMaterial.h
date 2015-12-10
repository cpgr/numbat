/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef DDCMATERIAL_H
#define DDCMATERIAL_H

#include "Material.h"

class DDCMaterial;

template<>
InputParameters validParams<DDCMaterial>();

class DDCMaterial : public Material
{
public:

  DDCMaterial(const InputParameters & parameters);

protected:

  virtual void computeQpProperties();

private:

  /// Porosity
  Real _material_porosity;
  /// Permeability tensor
  RealTensorValue _material_permeability;
  /// Gravity vector
  RealVectorValue _material_gravity;
  /// Viscosity
  Real _material_fluid_viscosity;
  /// Effective diffusivity
  Real _material_diffusivity;
  /// Water density
  Real _material_water_density;
  /// Solute density
  Real _material_solute_density;

  /**
   * Member references that will hold the User Object values for
   * the porous material properties.
   */
  MaterialProperty<Real> & _porosity;
  MaterialProperty<RealTensorValue> & _permeability;
  MaterialProperty<RealVectorValue> & _gravity;
  MaterialProperty<Real> & _viscosity;
  MaterialProperty<Real> & _diffusivity;
  MaterialProperty<Real> & _water_density;
  MaterialProperty<Real> & _solute_density;
  MaterialProperty<Real> & _density;
  MaterialProperty<RealVectorValue> & _velocity;
  MaterialProperty<Real> & _ddensity_dx;
  MaterialProperty<RealVectorValue> & _dvelocity_dx;
  MaterialProperty<RealTensorValue> & _dvelocity_dp;

  /**
   * Member references of the pressure and solute mass fraction variables
   */
  VariableGradient & _grad_pressure;
  VariableValue & _solute_mass_fraction;

  /**
   * Member references to the (optional) perturbations to the porosity and
   * permeability distributions
   */
  VariableValue & _porosity_noise;
  VariableValue & _permeability_noise;

};

#endif //DDCMATERIAL_H
