/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef DDCDARCYFLUXP_H
#define DDCDARCYFLUXP_H

#include "Kernel.h"

class DDCDarcyFluxP;

template<>
InputParameters validParams<DDCDarcyFluxP>();

class DDCDarcyFluxP : public Kernel
{
public:

  DDCDarcyFluxP(const InputParameters & parameters);

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

  /// Variable number of the solute mass fraction variable
  unsigned int _xvar;

};

#endif //DDCDARCYFLUXP_H
