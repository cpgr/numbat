/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef PERTURBATIONIC_H
#define PERTURBATIONIC_H

// MOOSE Includes
#include "InitialCondition.h"

// Forward Declarations
class PerturbationIC;

template<>
InputParameters validParams<PerturbationIC>();

/**
 * PerturbationIC just returns a constant value.
 */
class PerturbationIC : public InitialCondition
{
public:

  PerturbationIC(const InputParameters & parameters);

  /**
   * The value of the variable at a point.
   * This must be overriden by derived classes.
   */
  virtual Real value(const Point & p);

private:
  /// The amplitude of the initial perturbation
  Real _amplitude;
  /// Reference to the MOOSE mesh
  MooseMesh & _mesh;
  /// Component in the vertical direction (1 for 2D meshes, 2 for 3D meshes)
  unsigned int _component;
  /// Maximum value of mesh in the vertical direction
  Real _mesh_max;
};

#endif //PERTURBATIONIC_H
