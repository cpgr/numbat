/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatTotalMass.h"

template <>
InputParameters
validParams<NumbatTotalMass>()
{
  InputParameters params = validParams<ElementIntegralVariablePostprocessor>();
  params.addClassDescription("Calculates the total mass in model");
  return params;
}

NumbatTotalMass::NumbatTotalMass(const InputParameters & parameters)
  : ElementIntegralVariablePostprocessor(parameters),
    _porosity(getMaterialProperty<Real>("porosity")),
    _density(getMaterialProperty<Real>("density"))
{
}

Real
NumbatTotalMass::computeQpIntegral()
{
  return _porosity[_qp] * _density[_qp] * _u[_qp];
}
