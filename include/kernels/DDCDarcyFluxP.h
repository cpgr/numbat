/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef DDCDARCYFLUX_H
#define DDCDARCYFLUX_H

#include "Kernel.h"

class DDCDarcyFlux;

template<>
InputParameters validParams<DDCDarcyFlux>();

class DDCDarcyFlux : public Kernel
{
public:

  DDCDarcyFlux(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:

  /// Fluid density
  const MaterialProperty<Real> & _density;
  /// Fluid viscosity
  const MaterialProperty<Real> & _viscosity;
  /// Gravity
  const MaterialProperty<RealVectorValue> & _gravity;
  /// Permeability
  const MaterialProperty<RealTensorValue> & _permeability;
  /// Derivative of density wrt solute mass fraction
  const MaterialProperty<Real> & _ddensity_dx;

};

#endif //DDCDARCYFLUX_H
