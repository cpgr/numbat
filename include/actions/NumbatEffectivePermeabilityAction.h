/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATEFFECTIVEPERMEABILITYACTION_H
#define NUMBATEFFECTIVEPERMEABILITYACTION_H

#include "Action.h"
#include "libmesh/fe_type.h"
#include "MooseEnum.h"

class NumbatEffectivePermeabilityAction;

template <>
InputParameters validParams<NumbatEffectivePermeabilityAction>();

/**
 * Action to add all variables, kernels and postprocessors necessary
 * to calculate the effective permeability of a heterogeneous mesh
 */
class NumbatEffectivePermeabilityAction : public Action
{
public:
  NumbatEffectivePermeabilityAction(const InputParameters & parameters);

  virtual void act() override;

protected:
  /// Finite element type for the variable being created
  const FEType _fe_type;
  /// Scaling of variable
  const Real _scaling;
  /// Pressure variable
  const VariableName _pressure;
  /// Concentration variable
  const VariableName _concentration;
  /// Velocity AuxVariable name
  AuxVariableName _velocity;
  /// Direction to calculate effective permeability
  const MooseEnum _direction;
  /// Pressure at the inflow end (maximum pressure)
  const Real _pressure_inflow;
  /// Pressure at the outflow end (minimum pressure)
  const Real _pressure_outflow;
  /// Name of the inflow boundary
  const BoundaryName _boundary_inflow;
  /// Name of the outflow boundary
  const BoundaryName _boundary_outflow;
  /// Width of the mesh in the specified direction
  Real _width;
};

#endif // NUMBATEFFECTIVEPERMEABILITYACTION_H
