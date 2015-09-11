/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef DARCYDDC_H
#define DARCYDDC_H

#include "Kernel.h"

class DarcyDDC;

template<>
InputParameters validParams<DarcyDDC>();

class DarcyDDC : public Kernel
{
public:

  DarcyDDC(const InputParameters & parameters);

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
  /// The mesh dimension
  unsigned int _mesh_dimension;
};

#endif //DARCYDDC_H
