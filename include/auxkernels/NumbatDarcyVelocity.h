/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATDARCYVELOCITY_H
#define NUMBATDARCYVELOCITY_H

#include "AuxKernel.h"
#include "MooseMesh.h"

class NumbatDarcyVelocity;

template <>
InputParameters validParams<NumbatDarcyVelocity>();

class NumbatDarcyVelocity : public AuxKernel
{
public:
  NumbatDarcyVelocity(const InputParameters & parameters);

protected:
  virtual Real computeValue();

private:
  /// The gradient of the pressure
  const VariableGradient & _grad_pressure;
  /// Density
  const MaterialProperty<Real> & _density;
  /// Gravity
  RealVectorValue _gravity;
  /// Viscosity
  const MaterialProperty<Real> & _viscosity;
  /// Permeability tensor material property
  const MaterialProperty<RealTensorValue> & _permeability;
  /// The component of the velocity
  const MooseEnum & _component;
};

#endif // NUMBATDARCYVELOCITY_H
