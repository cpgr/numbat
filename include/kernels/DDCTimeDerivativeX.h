/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef DDCTIMEDERIVATIVEX_H
#define DDCTIMEDERIVATIVEX_H

#include "TimeDerivative.h"

class DDCTimeDerivativeX;

template<>
InputParameters validParams<DDCTimeDerivativeX>();

class DDCTimeDerivativeX : public TimeDerivative
{
public:

  DDCTimeDerivativeX(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:

  /// Porosity
  const MaterialProperty<Real> & _porosity;

  /// Density auxillary variable
  VariableValue & _density;
  /// Time derivative of the density auxillary variable
  VariableValue & _density_dot;

};

#endif //DDCTIMEDERIVATIVEX_H
