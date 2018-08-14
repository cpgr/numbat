/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

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
  /// Diffusion material property name
  const MaterialName _diffusivity_name;
  /// Diffusion coefficent
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
