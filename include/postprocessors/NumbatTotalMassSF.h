/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATTOTALMASSSF_H
#define NUMBATTOTALMASSSF_H

#include "ElementIntegralVariablePostprocessor.h"

class NumbatTotalMassSF;

template <>
InputParameters validParams<NumbatTotalMassSF>();

/**
 * Calculates total dimensionless mass in domain
 */
class NumbatTotalMassSF : public ElementIntegralVariablePostprocessor
{
public:
  NumbatTotalMassSF(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral() override;
};

#endif // NUMBATTOTALMASSSF_H
