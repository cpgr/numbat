/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATPOROSITY_H
#define NUMBATPOROSITY_H

#include "Material.h"

// Forward Declarations
class NumbatPorosity;

template <>
InputParameters validParams<NumbatPorosity>();

/**
 * Provides a porosity material property that may be constant
 * or provided by way of a coupled variable to simulate a heterogeneous
 * porosity.
 */
class NumbatPorosity : public Material
{
public:
  NumbatPorosity(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// Porosity (may be a coupled variable)
  const VariableValue & _input_porosity;
  /// Porosity material property
  MaterialProperty<Real> & _porosity;
};

#endif // NUMBATPOROSITY_H
