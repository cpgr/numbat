/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATDENSITY_H
#define NUMBATDENSITY_H

#include "Material.h"
#include "DerivativeMaterialInterface.h"

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
  const VariableName _concentration_var;
  /// Density at zero concentration
  const Real _zero_density_input;
  /// Density increase at equilibrium concentration
  const Real _delta_density_input;
  /// Fully saturated concentration
  const Real _saturated_concentration;
  /// Density material property
  MaterialProperty<Real> & _density;
  /// Density difference material property
  MaterialProperty<Real> & _delta_density;
  /// Derivative of density wrt concentration
  std::vector<MaterialProperty<Real> *> _ddensity_dc;
};

#endif // NUMBATDENSITY_H
