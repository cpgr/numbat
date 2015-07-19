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

#include "TwoDConvectionDiffusionDDC.h"

template<>
InputParameters validParams<TwoDConvectionDiffusionDDC>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredParam<RealTensorValue>("coeff_tensor", "Anisotropic diffusion tensor.");
  params.addRequiredCoupledVar("streamfunction_variable", "The gradient of the streamfunction will be used as the velocity vector.");
  return params;
}

TwoDConvectionDiffusionDDC::TwoDConvectionDiffusionDDC(const std::string & name,
                       InputParameters parameters) :
    Kernel(name, parameters),
    _gamma_tensor(getParam<RealTensorValue>("coeff_tensor")),
    _grad_streamfunction(coupledGradient("streamfunction_variable")),
    _grad_streamfunction_var(coupled("streamfunction_variable"))
{}

Real TwoDConvectionDiffusionDDC::computeQpResidual()
{
  Real convterm1 = - _test[_i][_qp] * (_grad_streamfunction[_qp](1) * _grad_u[_qp](0));
  Real convterm2 = _test[_i][_qp] * (_grad_streamfunction[_qp](0) * _grad_u[_qp](1));
  Real diffterm = (_gamma_tensor * _grad_u[_qp]) * _grad_test[_i][_qp];

  return convterm1 + convterm2 + diffterm;
}

Real TwoDConvectionDiffusionDDC::computeQpJacobian()
{
  Real dconvterm1 = - _test[_i][_qp] * (_grad_streamfunction[_qp](1) * _grad_phi[_j][_qp](0));
  Real dconvterm2 = _test[_i][_qp] * (_grad_streamfunction[_qp](0) * _grad_phi[_j][_qp](1));
  Real ddiffterm = (_gamma_tensor * _grad_phi[_j][_qp]) * _grad_test[_i][_qp];

  return dconvterm1 + dconvterm2 + ddiffterm;
}

Real TwoDConvectionDiffusionDDC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _grad_streamfunction_var)
  {
    Real dconvterm1 = - _test[_i][_qp] * (_grad_phi[_j][_qp](1) * _grad_u[_qp](0));
    Real dconvterm2 = _test[_i][_qp] * (_grad_phi[_j][_qp](0) * _grad_u[_qp](1));

    return dconvterm1 + dconvterm2;
  }

  return 0.0;
}
