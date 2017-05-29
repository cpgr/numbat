/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATDENSITY_H
#define NUMBATDENSITY_H

#include "DerivativeMaterialInterface.h"
#include "Material.h"

// Forward Declarations
class NumbatDensity;

template <>
InputParameters validParams<NumbatDensity>();

/**
 * Provides a density material property as a function of concentration
 */
class NumbatDensity : public DerivativeMaterialInterface<Material>
{
public:
  NumbatDensity(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// Concentration
  const VariableValue & _concentration;
  /// Concentration variable name
  const VariableName _concentration_name;
  /// Equilibrium concentration
  const Real _equilibrium_concentration;
  /// Density at zero concentration
  const Real _zero_density;
  /// Density increase at equilibrium concentration
  const Real _delta_density;
  /// Density material property
  MaterialProperty<Real> & _density;
  /// Derivative of densitywrt concentration
  MaterialProperty<Real> & _ddensity_dc;
};

#endif // NUMBATDENSITY_H
