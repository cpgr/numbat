/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef THREEDDARCYDDC_H
#define THREEDDARCYDDC_H

#include "Kernel.h"

class ThreeDDarcyDDC;

template<>
InputParameters validParams<ThreeDDarcyDDC>();

class ThreeDDarcyDDC : public Kernel
{
public:

  ThreeDDarcyDDC(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:

  /// Permeability anisotropy kv/kh
  Real _gamma;
  /// The gradient of the concentration variable
  VariableGradient & _grad_concentration;
  /// The variable number of the concentration variable
  unsigned int _grad_concentration_var;
  /// The component of the streamfunction variable
  const MooseEnum & _component;
};

#endif //THREEDDARCYDDC_H
