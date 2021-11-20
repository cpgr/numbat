/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatBeta.h"

registerMooseObject("NumbatApp", NumbatBeta);

InputParameters
NumbatBeta::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("pressure", "Pressure variable");
  params.addRequiredCoupledVar("temperature", "temperature variable");
  params.addRequiredParam<std::vector<Real>>("coefficients", "A, B, C, D, E");
  params.addClassDescription("Calculates Beta");
  return params;
}

NumbatBeta::NumbatBeta(const InputParameters & parameters)
  : AuxKernel(parameters),
    _pressure(coupledValue("pressure")),
    _temperature(coupledValue("temperature")),
    _coefficients(getParam<std::vector<Real>>("coefficients"))
{
}

Real
NumbatBeta::computeValue()
{
  return _coefficients[0] + _coefficients[1] * _temperature[_qp] +
         _coefficients[2] * _pressure[_qp] + _coefficients[3] * std::pow(_temperature[_qp], 2) +
         _coefficients[4] * std::pow(_pressure[_qp], 2);
}
