/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatRayleighNumber.h"
#include "MooseMesh.h"

registerMooseObject("NumbatApp", NumbatRayleighNumber);

template <>
InputParameters
validParams<NumbatRayleighNumber>()
{
  InputParameters params = validParams<ElementIntegralPostprocessor>();
  RealVectorValue g(0, 0, -9.81);
  params.addParam<RealVectorValue>(
      "gravity", g, "Gravity vector. Defaults to -9.81 in y direction for 2D, z direction for 3D");
  MooseEnum component("x y z", "z");
  params.addParam<MooseEnum>(
      "component",
      component,
      "The component pointing downwards in the direction of flow (default is z)");

  params.addParam<MaterialName>(
      "diffusivity_name",
      "diffusivity",
      "Name of the diffusivity material property associated with this concentration");

  params.addClassDescription("Calculates Rayleigh number");
  return params;
}

NumbatRayleighNumber::NumbatRayleighNumber(const InputParameters & parameters)
  : ElementIntegralPostprocessor(parameters),
    _delta_density(getMaterialProperty<Real>("delta_density")),
    _viscosity(getMaterialProperty<Real>("viscosity")),
    _porosity(getMaterialProperty<Real>("porosity")),
    _diffusivity_name(getParam<MaterialName>("diffusivity_name")),
    _diffusivity(getMaterialProperty<Real>(_diffusivity_name)),
    _permeability(getMaterialProperty<RealTensorValue>("permeability")),
    _gravity(getParam<RealVectorValue>("gravity")),
    _component(getParam<MooseEnum>("component"))

{
  _height = _mesh.getMaxInDimension(_component) - _mesh.getMinInDimension(_component);
  _abs_gravity = std::abs(_gravity(_component));
}

Real
NumbatRayleighNumber::computeQpIntegral()
{
  return _permeability[_qp](_component, _component) * _delta_density[_qp] * _abs_gravity * _height /
         (_porosity[_qp] * _viscosity[_qp] * _diffusivity[_qp]);
}
