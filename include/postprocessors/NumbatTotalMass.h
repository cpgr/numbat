/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATTOTALMASS_H
#define NUMBATTOTALMASS_H

#include "ElementIntegralVariablePostprocessor.h"

/**
 * Calculates total mass in domain
 */
class NumbatTotalMass : public ElementIntegralVariablePostprocessor
{
public:
  NumbatTotalMass(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpIntegral() override;

  /// Porosity
  const MaterialProperty<Real> & _porosity;
  /// Density
  const MaterialProperty<Real> & _density;
};

#endif // NUMBATTOTALMASS_H
