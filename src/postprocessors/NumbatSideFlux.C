/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatSideFlux.h"

registerMooseObject("NumbatApp", NumbatSideFlux);

template <>
InputParameters
validParams<NumbatSideFlux>()
{
  InputParameters params = validParams<SideIntegralVariablePostprocessor>();
  params.addClassDescription("Calculates the mass flux over the boundary");
  return params;
}

NumbatSideFlux::NumbatSideFlux(const InputParameters & parameters)
  : SideIntegralVariablePostprocessor(parameters),
    _porosity(getMaterialProperty<Real>("porosity")),
    _diffusivity(getMaterialProperty<Real>("diffusivity")),
    _density(getMaterialProperty<Real>("density"))
{
}

Real
NumbatSideFlux::computeQpIntegral()
{
  return -_porosity[_qp] * _diffusivity[_qp] * _density[_qp] * _grad_u[_qp] * _normals[_qp];
}
