/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatEffectivePermeability.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<NumbatEffectivePermeability>()
{
  InputParameters params = validParams<GeneralPostprocessor>();
  params.addRequiredParam<PostprocessorName>("flux", "Flux across boundary");
  params.addRequiredParam<Real>("p1", "Pressure at upstream boundary");
  params.addRequiredParam<Real>("p2", "Pressure at downstream boundary");
  params.addRequiredParam<PostprocessorName>("area", "Cross-sectional area");
  MooseEnum component("x y z", "z");
  params.addParam<MooseEnum>(
      "component", component, "The component in the direction of flow (default is z)");
  params.addClassDescription("Calculates effective permeability of equivalent homogeneous model");
  return params;
}

NumbatEffectivePermeability::NumbatEffectivePermeability(const InputParameters & parameters)
  : GeneralPostprocessor(parameters),
    _flux(getPostprocessorValue("flux")),
    _viscosity(getMaterialProperty<Real>("viscosity")),
    _permeability(getMaterialProperty<RealTensorValue>("permeability")),
    _component(getParam<MooseEnum>("component")),
    _p1(getParam<Real>("p1")),
    _p2(getParam<Real>("p2")),
    _area(getPostprocessorValue("area")),
    _mesh(_subproblem.mesh())
{
  _length = _mesh.getMaxInDimension(_component) - _mesh.getMinInDimension(_component);
}

Real
NumbatEffectivePermeability::getValue()
{
  return _flux * _viscosity[0] * _length / (_p1 - _p2) / _area;
}
