/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATPERMEABILITY_H
#define NUMBATPERMEABILITY_H

#include "Material.h"

// Forward Declarations
class NumbatPermeability;

template <>
InputParameters validParams<NumbatPermeability>();

/**
 * Provides a constant permeability tensor material property
 */
class NumbatPermeability : public Material
{
public:
  NumbatPermeability(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// Permeability
  const RealTensorValue _input_permeability;
  /// Permeability material property
  MaterialProperty<RealTensorValue> & _permeability;
};

#endif // NUMBATPERMEABILITY_H
