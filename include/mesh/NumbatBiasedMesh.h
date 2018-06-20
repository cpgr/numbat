/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATBIASEDMESH_H
#define NUMBATBIASEDMESH_H

#include "GeneratedMesh.h"

class NumbatBiasedMesh;

template <>
InputParameters validParams<NumbatBiasedMesh>();

/**
 * The spacing between nodes in the modified mesh is given by x_{i+1} =  x_i + delta for
 * i = 0, 1, ..., n+1, where n is the number of elements. The scaling paramter delta can
 * be calculated as delta = 2 (width - n * _initial_resolution) / (n(n-1)), where width
 * is the distance from the minimum to the maximum in the specified direction, and x0
 * is the target initial resolution.
 */
class NumbatBiasedMesh : public GeneratedMesh
{
public:
  NumbatBiasedMesh(const InputParameters & parameters);

  virtual void buildMesh() override;

protected:
  /// Target resolution at the refined end
  const Real _initial_resolution;
  /// enum of names to refer to the refined edge
  const enum class NumbatBiasedEnum { LEFT, RIGHT, TOP, BOTTOM, FRONT, BACK } _biased_enum;
  /// Flag to perform biasing
  const bool _is_biased;
};

#endif /* NUMBATBIASEDMESH_H */
