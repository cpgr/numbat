/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "ThreeDDarcyDDC.h"

template<>
InputParameters validParams<ThreeDDarcyDDC>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("gamma", 1.0, "The anisotropy ratio");
  params.addRequiredCoupledVar("concentration_variable", "The concentration variable");
  MooseEnum component("x y", "x");
  params.addParam<MooseEnum>("component", component, "The component of the streamfunction");
  return params;
}

ThreeDDarcyDDC::ThreeDDarcyDDC(const InputParameters & parameters) :
    Kernel(parameters),
    _gamma(getParam<Real>("gamma")),
    _grad_concentration(coupledGradient("concentration_variable")),
    _grad_concentration_var(coupled("concentration_variable")),
    _component(getParam<MooseEnum>("component"))
{}

Real ThreeDDarcyDDC::computeQpResidual()
{
  Real qpresidual;

  if (_component == "x")
    qpresidual = _gamma * _test[_i][_qp] * _grad_concentration[_qp](1) - _grad_test[_i][_qp] * _grad_u[_qp];

  else if (_component == "y")
    qpresidual = - _gamma * _test[_i][_qp] * _grad_concentration[_qp](0) - _grad_test[_i][_qp] * _grad_u[_qp];

  return  qpresidual;
}

Real ThreeDDarcyDDC::computeQpJacobian()
{
  /// Both components have the same Jacobian
  return - _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}

Real ThreeDDarcyDDC::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real qpoffdiagjacobian;

  if (jvar == _grad_concentration_var)
  {
    if (_component == "x")
      qpoffdiagjacobian = _gamma * _test[_i][_qp] * _grad_phi[_j][_qp](1);

    else if (_component == "y")
      qpoffdiagjacobian = - _gamma * _test[_i][_qp] * _grad_phi[_j][_qp](0);
  }
  else
    qpoffdiagjacobian = 0.0;

  return qpoffdiagjacobian;
}
