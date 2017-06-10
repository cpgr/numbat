/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATVISCOSITY_H
#define NUMBATVISCOSITY_H

#include "Material.h"

// Forward Declarations
class NumbatViscosity;

template <>
InputParameters validParams<NumbatViscosity>();

/**
 * Provides a viscosity material property
 */
class NumbatViscosity : public Material
{
public:
  NumbatViscosity(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// NumbatViscosity
  const Real _input_viscosity;
  /// Viscosity material property
  MaterialProperty<Real> & _viscosity;
};

#endif // NUMBATVISCOSITY_H
