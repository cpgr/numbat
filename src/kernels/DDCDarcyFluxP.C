/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "DDCDarcyFlux.h"

template<>
InputParameters validParams<DDCDarcyFlux>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

DDCDarcyFlux::DDCDarcyFlux(const InputParameters & parameters) :
    Kernel(parameters),
    _density(getMaterialProperty<Real>("density")),
    _viscosity(getMaterialProperty<Real>("viscosity")),
    _gravity(getMaterialProperty<RealVectorValue>("gravity")),
    _permeability(getMaterialProperty<RealTensorValue>("permeability")),
    _ddensity_dx(getMaterialProperty<Real>("ddensity_dx"))
{
}

Real
DDCDarcyFlux::computeQpResidual()
{
  return _grad_test[_i][_qp] * (_permeability[_qp] * (_grad_u[_qp] - _density[_qp] * _gravity[_qp])) / _viscosity[_qp];
}

Real
DDCDarcyFlux::computeQpJacobian()
{
  return _grad_test[_i][_qp] * (_permeability[_qp] * _grad_phi[_j][_qp]) / _viscosity[_qp];
}

Real
DDCDarcyFlux::computeQpOffDiagJacobian(unsigned int jvar)
{
  /// Derivative wrt solute mass fraction
  return - _grad_test[_i][_qp] * (_permeability[_qp] * _phi[_j][_qp] * _ddensity_dx[_qp] * _gravity[_qp]) / _viscosity[_qp];
}
