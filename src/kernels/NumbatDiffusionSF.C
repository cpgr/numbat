/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatDiffusionSF.h"

template <>
InputParameters
validParams<NumbatDiffusionSF>()
{
  InputParameters params = validParams<Kernel>();
  RealTensorValue isotropic_tensor(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
  params.addParam<RealTensorValue>(
      "anisotropic_tensor", isotropic_tensor, "Anisotropic coefficient tensor");
  params.addClassDescription("Diffusion kernel for the streamfunction formulation");
  return params;
}

NumbatDiffusionSF::NumbatDiffusionSF(const InputParameters & parameters)
  : Kernel(parameters), _gamma_tensor(getParam<RealTensorValue>("anisotropic_tensor"))
{
}

Real
NumbatDiffusionSF::computeQpResidual()
{
  return (_gamma_tensor * _grad_u[_qp]) * _grad_test[_i][_qp];
}

Real
NumbatDiffusionSF::computeQpJacobian()
{
  return (_gamma_tensor * _grad_phi[_j][_qp]) * _grad_test[_i][_qp];
}
