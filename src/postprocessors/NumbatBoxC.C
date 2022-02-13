/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatBoxC.h"

registerMooseObject("NumbatApp", NumbatBoxC);

template <>
InputParameters
validParams<NumbatBoxC>()
{
  InputParameters params = validParams<ElementIntegralVariablePostprocessor>();
  params.addClassDescription("Calculates the total mass in Box C");
  return params;
}

NumbatBoxC::NumbatBoxC(const InputParameters & parameters)
  : ElementIntegralVariablePostprocessor(parameters)
{
}

Real
NumbatBoxC::computeQpIntegral()
{
  const RealVectorValue normz(0, 1, 0);
  return std::abs(_grad_u[_qp] * normz);
}
