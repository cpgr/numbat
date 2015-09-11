/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "ThreeDConvectionDiffusionDDC.h"

template<>
InputParameters validParams<ThreeDConvectionDiffusionDDC>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredParam<RealTensorValue>("coeff_tensor", "Anisotropic diffusion tensor.");
  params.addRequiredCoupledVar("streamfunctionx_variable", "The gradient of the streamfunction will be used as the velocity vector.");
  params.addRequiredCoupledVar("streamfunctiony_variable", "The gradient of the streamfunction will be used as the velocity vector.");
  return params;
}

ThreeDConvectionDiffusionDDC::ThreeDConvectionDiffusionDDC(const InputParameters & parameters) :
    Kernel(parameters),
    _gamma(getParam<RealTensorValue>("coeff_tensor")),
    _grad_streamfunctiony(coupledGradient("streamfunctiony_variable")),
    _grad_streamfunctionx(coupledGradient("streamfunctionx_variable")),
    _grad_streamfunctionx_var(coupled("streamfunctionx_variable")),
    _grad_streamfunctiony_var(coupled("streamfunctiony_variable"))
{}

Real ThreeDConvectionDiffusionDDC::computeQpResidual()
{
  Real convterm1 = - _test[_i][_qp] * (_grad_streamfunctiony[_qp](2) * _grad_u[_qp](0));
  Real convterm2 = _test[_i][_qp] * (_grad_streamfunctionx[_qp](2) * _grad_u[_qp](1));
  Real convterm3 = _test[_i][_qp] * (_grad_streamfunctiony[_qp](0) - _grad_streamfunctionx[_qp](1)) * _grad_u[_qp](2);
  Real diffterm = (_gamma * _grad_u[_qp]) * _grad_test[_i][_qp];

  return convterm1 + convterm2 + convterm3 + diffterm;
}

Real ThreeDConvectionDiffusionDDC::computeQpJacobian()
{
  Real dconvterm1 = - _test[_i][_qp] * (_grad_streamfunctiony[_qp](2) * _grad_phi[_j][_qp](0));
  Real dconvterm2 = _test[_i][_qp] * (_grad_streamfunctionx[_qp](2) * _grad_phi[_j][_qp](1));
  Real dconvterm3 = _test[_i][_qp] * (_grad_streamfunctiony[_qp](0) - _grad_streamfunctionx[_qp](1)) * _grad_phi[_j][_qp](2);
  Real ddiffterm = (_gamma * _grad_phi[_j][_qp]) * _grad_test[_i][_qp];

  return dconvterm1 + dconvterm2 + dconvterm3 + ddiffterm;
}

/*
Real ThreeDConvectionDiffusionDDC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _grad_streamfunction_var)
  {
    Real dconvterm1 = - _test[_i][_qp] * (_grad_phi[_j][_qp](1) * _grad_u[_qp](0));
    Real dconvterm2 = _test[_i][_qp] * (_grad_phi[_j][_qp](0) * _grad_u[_qp](1));

    return dconvterm1 + dconvterm2;
  }

  return 0.0;
}
*/
