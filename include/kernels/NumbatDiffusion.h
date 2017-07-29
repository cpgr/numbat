/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATDIFFUSION_H
#define NUMBATDIFFUSION_H

#include "Diffusion.h"

class NumbatDiffusion;

template <>
InputParameters validParams<NumbatDiffusion>();

class NumbatDiffusion : public Diffusion
{
public:
  NumbatDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  /// Porosity
  const MaterialProperty<Real> & _porosity;
  /// Diffusion
  const MaterialProperty<Real> & _diffusivity;
};

#endif // NUMBATDIFFUSION_H
