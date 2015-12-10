/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "DDCDarcyFluxX.h"

template<>
InputParameters validParams<DDCDarcyFluxX>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("pressure_variable", "The pressure variable");
  return params;
}

DDCDarcyFluxX::DDCDarcyFluxX(const InputParameters & parameters) :
    Kernel(parameters),
    _density(getMaterialProperty<Real>("density")),
    _velocity(getMaterialProperty<RealVectorValue>("velocity")),
    _ddensity_dx(getMaterialProperty<Real>("ddensity_dx")),
    _dvelocity_dx(getMaterialProperty<RealVectorValue>("dvelocity_dx")),
    _dvelocity_dp(getMaterialProperty<RealTensorValue>("dvelocity_dp")),
    _pvar(coupled("pressure_variable"))
{
}

Real
DDCDarcyFluxX::computeQpResidual()
{
  return _grad_test[_i][_qp] * _density[_qp] * _velocity[_qp] * _u[_qp];
}

Real
DDCDarcyFluxX::computeQpJacobian()
{
  RealVectorValue qpjacobian;
  qpjacobian = _ddensity_dx[_qp] * _velocity[_qp] * _u[_qp];
  qpjacobian += _density[_qp] * _dvelocity_dx[_qp] * _u[_qp];
  qpjacobian += _density[_qp] * _velocity[_qp];

  return _grad_test[_i][_qp] * _phi[_j][_qp] * qpjacobian;
}

Real
DDCDarcyFluxX::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real qpoffdiagjacobian = 0.0;

  if (jvar == _pvar)
  {
    /// Derivative wrt pressure
    qpoffdiagjacobian = _grad_test[_i][_qp] * _density[_qp] * (_dvelocity_dp[_qp] * _grad_phi[_j][_qp] * _u[_qp]);
  }

  return qpoffdiagjacobian;
}
