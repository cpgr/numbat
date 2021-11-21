/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATTOTALMASSSF_H
#define NUMBATTOTALMASSSF_H

#include "ElementIntegralVariablePostprocessor.h"

/**
 * Calculates total dimensionless mass in domain
 */
class NumbatTotalMassSF : public ElementIntegralVariablePostprocessor
{
public:
  NumbatTotalMassSF(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpIntegral() override;
};

#endif // NUMBATTOTALMASSSF_H
