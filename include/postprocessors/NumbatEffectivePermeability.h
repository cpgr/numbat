/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATEFFECTIVEPERMEABILITY_H
#define NUMBATEFFECTIVEPERMEABILITY_H

#include "GeneralPostprocessor.h"

class NumbatEffectivePermeability;
class MooseMesh;

template <>
InputParameters validParams<NumbatEffectivePermeability>();

/**
 * Calculates effective permeability assuming model is represented by a
 * homogeneous model using Darcy's law
 */
class NumbatEffectivePermeability : public GeneralPostprocessor
{
public:
  NumbatEffectivePermeability(const InputParameters & parameters);

protected:
  virtual void initialize() override {}
  virtual void execute() override {}
  virtual Real getValue() override;

  /// Flux across boundary
  const PostprocessorValue & _flux;
  /// Viscosity
  const MaterialProperty<Real> & _viscosity;
  /// Direction of flow
  const MooseEnum & _component;
  /// Length of the model in direction of flow
  Real _length;
  /// Value of pressure at upstream boundary
  Real _p1;
  /// Value of pressure at downstream boundary
  Real _p2;
  /// Cross sectional area
  const PostprocessorValue & _area;
  /// MooseMesh
  MooseMesh & _mesh;
};

#endif // NUMBATEFFECTIVEPERMEABILITY_H
