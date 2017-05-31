/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "DarcyVelocityAux.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<DarcyVelocityAux>()
{
  InputParameters params = validParams<AuxKernel>();
  RealVectorValue g(0, 0, -9.81);
  params.addParam<RealVectorValue>(
      "gravity", g, "Gravity vector. Defaults to -9.81 in y direction for 2D, z direction for 3D");
  params.addRequiredCoupledVar("pressure", "Pressure variable");
  MooseEnum component("x y z", "x");
  params.addParam<MooseEnum>("component", component, "The component of the velocity");
  return params;
}

DarcyVelocityAux::DarcyVelocityAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _grad_pressure(coupledGradient("pressure")),
    _density(getMaterialProperty<Real>("density")),
    _gravity(getParam<RealVectorValue>("gravity")),
    _viscosity(getMaterialProperty<Real>("viscosity")),
    _permeability(getMaterialProperty<RealTensorValue>("permeability")),
    _component(getParam<MooseEnum>("component"))
{
  // If gravity hasn't been provided, use a value of -9.81 in the y direction
  // for 2D, or in the z direction for 3D (which is the default)
  if (!parameters.isParamSetByUser("gravity"))
    if (_mesh.dimension() == 2)
      _gravity = RealVectorValue(0, -9.81, 0);
}

Real
DarcyVelocityAux::computeValue()
{
  return -(_permeability[_qp] / _viscosity[_qp] *
           (_grad_pressure[_qp] - _density[_qp] * _gravity))(_component);
}
