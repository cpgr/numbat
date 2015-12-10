/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef DDCDIFFUSIONX_H
#define DDCDIFFUSIONX_H

#include "Kernel.h"

class DDCDiffusionX;

template<>
InputParameters validParams<DDCDiffusionX>();

class DDCDiffusionX : public Kernel
{
public:

  DDCDiffusionX(const InputParameters & parameters);

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
  /// Derivative of density wrt solute mass fraction
  const MaterialProperty<Real> & _ddensity_dx;

};

#endif //DDCDIFFUSIONX_H
