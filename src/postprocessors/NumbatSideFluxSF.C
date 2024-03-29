/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatSideFluxSF.h"

registerMooseObject("NumbatApp", NumbatSideFluxSF);

InputParameters
NumbatSideFluxSF::validParams()
{
  InputParameters params = SideIntegralVariablePostprocessor::validParams();
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
