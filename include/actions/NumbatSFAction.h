/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATSFACTION_H
#define NUMBATSFACTION_H

#include "Action.h"
#include "libmesh/fe_type.h"
#include "MooseEnum.h"

class NumbatSFAction;

template <>
InputParameters validParams<NumbatSFAction>();

/**
 * Action to add all variables, kernels etc for both 2D and 3D
 * models for the dimensionless streamfunction formulation
 */
class NumbatSFAction : public Action
{
public:
  NumbatSFAction(const InputParameters & parameters);

  virtual void act() override;

protected:
  /// Finite element type for the variable being created
  const FEType _fe_type;
  /// Scaling of variable
  const Real _scaling;
  /// Concentration variable
  VariableName _concentration;
  /// Streamfunction variable(s)
  std::vector<VariableName> _streamfunction;
  /// Anisotropy of porous medium
  const Real _gamma;
  /// Velocity AuxVariable names
  std::vector<AuxVariableName> _aux;
  /// Flag to set periodic boundary conditions
  const bool _periodic_bcs;
};

#endif // NUMBATSFACTION_H
