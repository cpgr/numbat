/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatDiffusivity.h"

registerMooseObject("NumbatApp", NumbatDiffusivity);

template <>
InputParameters
validParams<NumbatDiffusivity>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("diffusivity", "The diffusivity");
  params.addParam<MaterialName>(
      "diffusivity_name", "diffusivity", "Name of the diffusivity material property");
  params.addClassDescription("This Material provides a diffusivity material property");
  return params;
}

NumbatDiffusivity::NumbatDiffusivity(const InputParameters & parameters)
  : Material(parameters),
    _diffusivity_name(getParam<MaterialName>("diffusivity_name")),
    _input_diffusivity(coupledValue("diffusivity")),
    _diffusivity(declareProperty<Real>(_diffusivity_name))
{
}

void
NumbatDiffusivity::computeQpProperties()
{
  _diffusivity[_qp] = _input_diffusivity[_qp];
}
