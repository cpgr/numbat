/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "DDCDarcyFluxP.h"

template<>
InputParameters validParams<DDCDarcyFluxP>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("solute_mass_fraction_variable", "The solute mass fraction variable");
  return params;
}

DDCDarcyFluxP::DDCDarcyFluxP(const InputParameters & parameters) :
    Kernel(parameters),
    _density(getMaterialProperty<Real>("density")),
    _viscosity(getMaterialProperty<Real>("viscosity")),
    _gravity(getMaterialProperty<RealVectorValue>("gravity")),
    _permeability(getMaterialProperty<RealTensorValue>("permeability")),
    _ddensity_dx(getMaterialProperty<Real>("ddensity_dx")),
    _xvar(coupled("solute_mass_fraction_variable"))
{
}

Real
DDCDarcyFluxP::computeQpResidual()
{
  return _grad_test[_i][_qp] * (_permeability[_qp] * (_grad_u[_qp] - _density[_qp] * _gravity[_qp])) / _viscosity[_qp];
}

Real
DDCDarcyFluxP::computeQpJacobian()
{
  return _grad_test[_i][_qp] * (_permeability[_qp] * _grad_phi[_j][_qp]) / _viscosity[_qp];
}

Real
DDCDarcyFluxP::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real qpoffdiagjacobian = 0.0;

  if (jvar == _xvar)
  {
    /// Derivative wrt solute mass fraction
    qpoffdiagjacobian = - _grad_test[_i][_qp] * (_permeability[_qp] * _phi[_j][_qp] * _ddensity_dx[_qp] * _gravity[_qp]) / _viscosity[_qp];
  }

  return qpoffdiagjacobian;
}
