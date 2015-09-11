/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef THREEDDARCYDDCY_H
#define THREEDDARCYDDCY_H

#include "Kernel.h"

class ThreeDDarcyDDCy;

template<>
InputParameters validParams<ThreeDDarcyDDCy>();

class ThreeDDarcyDDCy : public Kernel
{
public:

  ThreeDDarcyDDCy(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:

  Real _gamma;
  VariableGradient & _grad_concentration;
  unsigned int _grad_concentration_var;
};

#endif //THREEDDARCYDDCY_H
