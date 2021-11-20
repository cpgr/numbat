/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATSIDEFLUX_H
#define NUMBATSIDEFLUX_H

#include "SideIntegralVariablePostprocessor.h"

/**
 * Calculates flux over boundary
 */
class NumbatSideFlux : public SideIntegralVariablePostprocessor
{
public:
  NumbatSideFlux(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpIntegral() override;

  /// Porosity
  const MaterialProperty<Real> & _porosity;
  /// Diffusivity material name
  const MaterialName _diffusivity_name;
  /// Diffusivity
  const MaterialProperty<Real> & _diffusivity;
  /// Density
  const MaterialProperty<Real> & _density;
};

#endif // NUMBATSIDEFLUX_H
