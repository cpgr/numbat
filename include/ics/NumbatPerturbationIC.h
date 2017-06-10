/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATPERTURBATIONIC_H
#define NUMBATPERTURBATIONIC_H

// MOOSE Includes
#include "InitialCondition.h"

// Forward Declarations
class NumbatPerturbationIC;

template <>
InputParameters validParams<NumbatPerturbationIC>();

/**
 * NumbatPerturbationIC just returns a constant value.
 */
class NumbatPerturbationIC : public InitialCondition
{
public:
  NumbatPerturbationIC(const InputParameters & parameters);

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

#endif // NUMBATPERTURBATIONIC_H
