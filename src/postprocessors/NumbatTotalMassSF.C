/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatTotalMassSF.h"

registerMooseObject("NumbatApp", NumbatTotalMassSF);

template <>
InputParameters
validParams<NumbatTotalMassSF>()
{
  InputParameters params = validParams<ElementIntegralVariablePostprocessor>();
  params.addClassDescription(
      "Calculates the total dimensionless mass in model for the streamfunction formulation");
  return params;
}

NumbatTotalMassSF::NumbatTotalMassSF(const InputParameters & parameters)
  : ElementIntegralVariablePostprocessor(parameters)
{
}

Real
NumbatTotalMassSF::computeQpIntegral()
{
  return _u[_qp];
}
