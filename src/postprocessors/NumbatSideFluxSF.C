/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatSideFluxSF.h"

template <>
InputParameters
validParams<NumbatSideFluxSF>()
{
  InputParameters params = validParams<SideIntegralVariablePostprocessor>();
  params.addClassDescription("Calculates the dimensionless mass flux over the boundary for the "
                             "streamfunction formulation");
  return params;
}

NumbatSideFluxSF::NumbatSideFluxSF(const InputParameters & parameters)
  : SideIntegralVariablePostprocessor(parameters)
{
}

Real
NumbatSideFluxSF::computeQpIntegral()
{
  return -_grad_u[_qp] * _normals[_qp];
}
