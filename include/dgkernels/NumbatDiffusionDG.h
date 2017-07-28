/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATDIFFUSIONDG_H
#define NUMBATDIFFUSIONDG_H

#include "DGDiffusion.h"

class NumbatDiffusionDG;

template <>
InputParameters validParams<NumbatDiffusionDG>();

class NumbatDiffusionDG : public DGKernel
{
public:
  NumbatDiffusionDG(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type) override;
  virtual Real computeQpJacobian(Moose::DGJacobianType type) override;

  const Real _epsilon;
  const Real _sigma;
  /// Porosity
  const MaterialProperty<Real> & _porosity;
  /// Porosity of the neighbouring element
  const MaterialProperty<Real> & _porosity_neighbor;
  /// Diffusivity
  const MaterialProperty<Real> & _diffusivity;
  /// Diffusivity of the neighbouring element
  const MaterialProperty<Real> & _diffusivity_neighbor;
};

#endif // NUMBATDIFFUSIONDG_H
