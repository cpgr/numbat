/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATDIFFUSIVITY_H
#define NUMBATDIFFUSIVITY_H

#include "Material.h"

/**
 * Provides a diffusivity material property that may be constant
 * or provided by way of a coupled variable to simulate a heterogeneous
 * diffusivity.
 */
class NumbatDiffusivity : public Material
{
public:
  NumbatDiffusivity(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void computeQpProperties() override;

  /// Name of the diffusivity material property
  const MaterialName _diffusivity_name;
  /// Diffusivity (may be a coupled variable)
  const VariableValue & _input_diffusivity;
  /// Diffusivity material property
  MaterialProperty<Real> & _diffusivity;
};

#endif // NUMBATDIFFUSIVITY_H
