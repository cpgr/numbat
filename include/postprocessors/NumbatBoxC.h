/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATBOXC_H
#define NUMBATBOXC_H

#include "ElementIntegralVariablePostprocessor.h"

class NumbatBoxC;

template <>
InputParameters validParams<NumbatBoxC>();

/**
 * Calculates total mass in domain
 */
class NumbatBoxC : public ElementIntegralVariablePostprocessor
{
public:
  NumbatBoxC(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral() override;
};

#endif // NUMBATBOXC_H
