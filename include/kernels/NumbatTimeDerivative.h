/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATTIMEDERIVATIVE_H
#define NUMBATTIMEDERIVATIVE_H

#include "TimeDerivative.h"

class NumbatTimeDerivative;

template <>
InputParameters validParams<NumbatTimeDerivative>();

class NumbatTimeDerivative : public TimeDerivative
{
public:
  NumbatTimeDerivative(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  /// Porosity
  const MaterialProperty<Real> & _porosity;
};

#endif // NUMBATTIMEDERIVATIVE_H
