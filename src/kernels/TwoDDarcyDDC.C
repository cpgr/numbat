/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "TwoDDarcyDDC.h"

template<>
InputParameters validParams<TwoDDarcyDDC>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("gamma", 1.0, "The anisotropy ratio");
  params.addRequiredCoupledVar("concentration_variable", "The gradient of the concentration is passed for the coupling.");
  return params;
}

TwoDDarcyDDC::TwoDDarcyDDC(const InputParameters & parameters) :
    Kernel(parameters),
    _gamma(getParam<Real>("gamma")),
    _grad_concentration(coupledGradient("concentration_variable")),
    _grad_concentration_var(coupled("concentration_variable"))
{}

Real TwoDDarcyDDC::computeQpResidual()
{
  return  _gamma * _test[_i][_qp] * _grad_concentration[_qp](0) - _grad_test[_i][_qp] * _grad_u[_qp];
}

Real TwoDDarcyDDC::computeQpJacobian()
{
  return - _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}

Real TwoDDarcyDDC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _grad_concentration_var)
    return _gamma * _test[_i][_qp] * _grad_phi[_j][_qp](0);
  return 0.0;
}
