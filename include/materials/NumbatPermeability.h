/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATPERMEABILITY_H
#define NUMBATPERMEABILITY_H

#include "Material.h"

/**
 * Provides a constant permeability tensor material property
 */
class NumbatPermeability : public Material
{
public:
  NumbatPermeability(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void computeQpProperties() override;

  /// Permeability
  const RealTensorValue _input_permeability;
  /// Permeability material property
  MaterialProperty<RealTensorValue> & _permeability;
};

#endif // NUMBATPERMEABILITY_H
