/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef DDCDIFFUSION_H
#define DDCDIFFUSION_H

#include "Kernel.h"

class DDCDiffusion;

template<>
InputParameters validParams<DDCDiffusion>();

class DDCDiffusion : public Kernel
{
public:

  DDCDiffusion(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:

  /// Porosity
  const MaterialProperty<Real> & _porosity;
  /// Fluid density
  const MaterialProperty<Real> & _density;
  /// Effective diffusivity
  const MaterialProperty<Real> & _diffusivity;
  /// Water density
  const MaterialProperty<Real> & _water_density;
  /// Solute density
  const MaterialProperty<Real> & _solute_density;

};

#endif //DDCDIFFUSION_H
