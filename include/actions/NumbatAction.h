/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATACTION_H
#define NUMBATACTION_H

#include "Action.h"
#include "libmesh/fe_type.h"
#include "libmesh/vector_value.h"
#include "MooseEnum.h"

/**
 * Action to add all variables, kernels etc for both 2D and 3D
 * models for the dimensionsl formulation
 */
class NumbatAction : public Action
{
public:
  NumbatAction(const InputParameters & parameters);

  static InputParameters validParams();

  virtual void act() override;

protected:
  /// Finite element type for the variable being created
  const FEType _fe_type;
  /// Scaling of concentration variable (default is 1)
  const Real _concentration_scaling;
  /// Scaling of pressure variable (default is 1)
  const Real _pressure_scaling;
  /// Concentration variable
  const VariableName _concentration;
  /// Pressure variable
  const VariableName _pressure;
  /// Concentration at constant concentration boundary
  const Real _boundary_concentration;
  /// Velocity AuxVariable names
  std::vector<AuxVariableName> _aux;
  /// Flag to set periodic boundary conditions
  const bool _periodic_bcs;
  /// Gravity
  RealVectorValue _gravity;
};

#endif // NUMBATACTION_H
