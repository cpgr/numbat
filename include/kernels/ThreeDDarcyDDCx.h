/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef THREEDDARCYDDCX_H
#define THREEDDARCYDDCX_H

#include "Kernel.h"

class ThreeDDarcyDDCx;

template<>
InputParameters validParams<ThreeDDarcyDDCx>();

class ThreeDDarcyDDCx : public Kernel
{
public:

  ThreeDDarcyDDCx(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:

  Real _gamma;
  VariableGradient & _grad_concentration;
  unsigned int _grad_concentration_var;
};

#endif //THREEDDARCYDDCX_H
