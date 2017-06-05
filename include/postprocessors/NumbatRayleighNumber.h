/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATRAYLEIGHNUMBER_H
#define NUMBATRAYLEIGHNUMBER_H

#include "ElementIntegralPostprocessor.h"

class NumbatRayleighNumber;

template <>
InputParameters validParams<NumbatRayleighNumber>();

/**
 * Calculates Rayleigh number of problem
 */
class NumbatRayleighNumber : public ElementIntegralPostprocessor
{
public:
  NumbatRayleighNumber(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral() override;

  /// Density
  const MaterialProperty<Real> & _delta_density;
  /// Viscosity
  const MaterialProperty<Real> & _viscosity;
  /// Porosity
  const MaterialProperty<Real> & _porosity;
  /// Diffusivity
  const MaterialProperty<Real> & _diffusivity;
  /// Permeability
  const MaterialProperty<RealTensorValue> & _permeability;
  /// Gravity
  RealVectorValue _gravity;
  /// Absolute value of gravity
  Real _abs_gravity;
  /// Downward direction
  const MooseEnum & _component;
  /// Height of the model
  Real _height;
};

#endif // NUMBATRAYLEIGHNUMBER_H
