/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATDENSITYMULTIPLESPECIES_H
#define NUMBATDENSITYMULTIPLESPECIES_H

#include "Material.h"
#include "DerivativeMaterialInterface.h"

class NumbatDensityMultipleSpecies;

template <>
InputParameters validParams<NumbatDensityMultipleSpecies>();

/**
 * Provides a density material property as a function of concentration of
 * multiple species
 */
class NumbatDensityMultipleSpecies : public DerivativeMaterialInterface<Material>
{
public:
  NumbatDensityMultipleSpecies(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// Number of coupled species
  const unsigned int _num_species;
  /// Concentration(s)
  std::vector<const VariableValue *> _concentration;
  /// Concentration variable name(s)
  std::vector<VariableName> _concentration_var;
  /// Coefficients of concentration(s)
  std::vector<const VariableValue *> _coefficients;
  /// Unsaturated density
  const Real _unsaturated_density;
  /// Density
  MaterialProperty<Real> & _density;
  /// Derivative of density wrt concentration(s)
  std::vector<MaterialProperty<Real> *> _ddensity_dc;
};

#endif // NUMBATDENSITYMULTIPLESPECIES_H
