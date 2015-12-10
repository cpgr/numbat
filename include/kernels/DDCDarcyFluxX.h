/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef DDCDARCYFLUXX_H
#define DDCDARCYFLUXX_H

#include "Kernel.h"

class DDCDarcyFluxX;

template<>
InputParameters validParams<DDCDarcyFluxX>();

class DDCDarcyFluxX : public Kernel
{
public:

  DDCDarcyFluxX(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:

  /// Fluid density
  const MaterialProperty<Real> & _density;
  /// Fluid velocity
  const MaterialProperty<RealVectorValue> & _velocity;
  /// Derivative of density wrt solute mass fraction
  const MaterialProperty<Real> & _ddensity_dx;
  /// Derivative of Darcy velocity wrt solute mass fraction
  const MaterialProperty<RealVectorValue> & _dvelocity_dx;
  /// Derivative of Darcy velocity wrt pressure
  const MaterialProperty<RealTensorValue> & _dvelocity_dp;

  /// Variable number of the pressure variable
  unsigned int _pvar;

};

#endif //DDCDARCYFLUXX_H
