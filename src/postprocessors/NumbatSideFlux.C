/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatSideFlux.h"

registerMooseObject("NumbatApp", NumbatSideFlux);

InputParameters
NumbatSideFlux::validParams()
{
  InputParameters params = SideIntegralVariablePostprocessor::validParams();
  params.addParam<MaterialName>(
      "diffusivity_name",
      "diffusivity",
      "Name of the diffusivity material property associated with this concentration");
  params.addClassDescription("Calculates the mass flux over the boundary");
  return params;
}

NumbatSideFlux::NumbatSideFlux(const InputParameters & parameters)
  : SideIntegralVariablePostprocessor(parameters),
    _porosity(getMaterialProperty<Real>("porosity")),
    _diffusivity_name(getParam<MaterialName>("diffusivity_name")),
    _diffusivity(getMaterialProperty<Real>(_diffusivity_name)),
    _density(getMaterialProperty<Real>("density"))
{
}

Real
NumbatSideFlux::computeQpIntegral()
{
  return -_porosity[_qp] * _diffusivity[_qp] * _density[_qp] * _grad_u[_qp] * _normals[_qp];
}
