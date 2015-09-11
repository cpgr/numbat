/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef TWODDARCYDDC_H
#define TWODDARCYDDC_H

#include "Kernel.h"

class TwoDDarcyDDC;

template<>
InputParameters validParams<TwoDDarcyDDC>();

class TwoDDarcyDDC : public Kernel
{
public:

  TwoDDarcyDDC(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:

  Real _gamma;
  VariableGradient & _grad_concentration;
  unsigned int _grad_concentration_var;
};

#endif //TWODDARCYDDC_H
