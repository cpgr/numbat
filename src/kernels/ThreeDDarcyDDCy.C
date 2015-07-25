/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "ThreeDDarcyDDCy.h"

template<>
InputParameters validParams<ThreeDDarcyDDCy>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("gamma", 1.0, "The anisotropy ratio");
  params.addRequiredCoupledVar("concentration_variable", "The gradient of the concentration is passed for the coupling.");
  return params;
}

ThreeDDarcyDDCy::ThreeDDarcyDDCy(const InputParameters & parameters) :
    Kernel(parameters),
    _gamma(getParam<Real>("gamma")),
    _grad_concentration(coupledGradient("concentration_variable")),
    _grad_concentration_var(coupled("concentration_variable"))
{}

Real ThreeDDarcyDDCy::computeQpResidual()
{
  return - _gamma * _test[_i][_qp] * _grad_concentration[_qp](0) - _grad_test[_i][_qp] * _grad_u[_qp];
}

Real ThreeDDarcyDDCy::computeQpJacobian()
{
  return - _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}

Real ThreeDDarcyDDCy::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _grad_concentration_var)
    return - _gamma * _test[_i][_qp] * _grad_phi[_j][_qp](0);
  return 0.0;
}
