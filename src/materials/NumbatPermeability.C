/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NumbatPermeability.h"

template <>
InputParameters
validParams<NumbatPermeability>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredParam<RealTensorValue>("permeability", "The permeability tensor");
  params.addClassDescription("This Material provides a constant permeability material property");
  return params;
}

NumbatPermeability::NumbatPermeability(const InputParameters & parameters)
  : Material(parameters),
    _input_permeability(getParam<RealTensorValue>("permeability")),
    _permeability(declareProperty<RealTensorValue>("permeability"))
{
}

void
NumbatPermeability::computeQpProperties()
{
  _permeability[_qp] = _input_permeability;
}
