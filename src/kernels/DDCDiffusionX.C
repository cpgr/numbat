/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "DDCDiffusionX.h"

template<>
InputParameters validParams<DDCDiffusionX>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

DDCDiffusionX::DDCDiffusionX(const InputParameters & parameters) :
    Kernel(parameters),
    _porosity(getMaterialProperty<Real>("porosity")),
    _density(getMaterialProperty<Real>("density")),
    _diffusivity(getMaterialProperty<Real>("diffusivity")),
    _ddensity_dx(getMaterialProperty<Real>("ddensity_dx"))
{
}

Real
DDCDiffusionX::computeQpResidual()
{
  return _grad_test[_i][_qp] * _density[_qp] * _porosity[_qp] * _diffusivity[_qp] * _grad_u[_qp];
}

Real
DDCDiffusionX::computeQpJacobian()
{
  RealVectorValue qpjacobian;
  qpjacobian = _density[_qp] * _grad_phi[_j][_qp] + _phi[_j][_qp] * _ddensity_dx[_qp] * _grad_u[_qp];

  return _grad_test[_i][_qp] * _porosity[_qp] * _diffusivity[_qp] * qpjacobian;
}

Real
DDCDiffusionX::computeQpOffDiagJacobian(unsigned int jvar)
{
  return 0.0;
}
