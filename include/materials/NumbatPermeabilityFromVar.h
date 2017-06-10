/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATPERMEABILITYFROMVAR_H
#define NUMBATPERMEABILITYFROMVAR_H

#include "Material.h"

// Forward Declarations
class NumbatPermeabilityFromVar;

template <>
InputParameters validParams<NumbatPermeabilityFromVar>();

/**
 * Provides a permeability tensor material property from coupled variables,
 * enabling a spatially varying heterogeneous permeability.
 *
 * The three diagonal entries corresponding to the x, y, and z directions
 * must be given. Optionally, the off-diagonal components of the full
 * permeability tensor can be given. If they are not provided, they will be
 * initialised to zero.
 */
class NumbatPermeabilityFromVar : public Material
{
public:
  NumbatPermeabilityFromVar(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// Permeability components
  const VariableValue & _perm_xx;
  const VariableValue & _perm_xy;
  const VariableValue & _perm_xz;
  const VariableValue & _perm_yx;
  const VariableValue & _perm_yy;
  const VariableValue & _perm_yz;
  const VariableValue & _perm_zx;
  const VariableValue & _perm_zy;
  const VariableValue & _perm_zz;
  /// Permeability material property
  MaterialProperty<RealTensorValue> & _permeability;
};

#endif // NUMBATPERMEABILITYFROMVAR_H
