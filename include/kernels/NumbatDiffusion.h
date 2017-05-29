/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

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
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  /// Porosity
  const MaterialProperty<Real> & _porosity;
  /// Diffusion
  const MaterialProperty<Real> & _diffusivity;
};

#endif // NUMBATDIFFUSION_H
