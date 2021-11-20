/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATDIFFUSIONDGBC_H
#define NUMBATDIFFUSIONDGBC_H

#include "IntegratedBC.h"

/**
 * Dirichlet boundary condition for concentration in the DG formulation
 */
class NumbatDiffusionDGBC : public IntegratedBC
{
public:
  NumbatDiffusionDGBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  /// Value for this BC
  const Real & _value;
  /// epsilon
  const Real _epsilon;
  /// sigma
  const Real _sigma;
  /// Porosity
  const MaterialProperty<Real> & _porosity;
  /// Diffusivity
  const MaterialProperty<Real> & _diffusivity;
};

#endif // NUMBATDIFFUSIONDGBC_H
