/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATDIFFUSIVITY_H
#define NUMBATDIFFUSIVITY_H

#include "Material.h"

// Forward Declarations
class NumbatDiffusivity;

template <>
InputParameters validParams<NumbatDiffusivity>();

/**
 * Provides a diffusivity material property that may be constant
 * or provided by way of a coupled variable to simulate a heterogeneous
 * diffusivity.
 */
class NumbatDiffusivity : public Material
{
public:
  NumbatDiffusivity(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// Diffusivity (may be a coupled variable)
  const VariableValue & _input_diffusivity;
  /// Diffusivity material property
  MaterialProperty<Real> & _diffusivity;
};

#endif // NUMBATDIFFUSIVITY_H
