/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATBETA_H
#define NUMBATBETA_H

#include "AuxKernel.h"

class NumbatBeta : public AuxKernel
{
public:
  NumbatBeta(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue();

private:
  /// The pressure
  const VariableValue & _pressure;
  /// The temperature
  const VariableValue & _temperature;
  /// The coefficents
  const std::vector<Real> _coefficients;
};

#endif // NUMBATBETA_H
