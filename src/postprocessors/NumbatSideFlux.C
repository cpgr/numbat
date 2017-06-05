/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NumbatSideFlux.h"

template <>
InputParameters
validParams<NumbatSideFlux>()
{
  InputParameters params = validParams<SideIntegralVariablePostprocessor>();
  params.addClassDescription("Calculates the flux over the boundary");
  return params;
}

NumbatSideFlux::NumbatSideFlux(const InputParameters & parameters)
  : SideIntegralVariablePostprocessor(parameters),
    _porosity(getMaterialProperty<Real>("porosity")),
    _diffusivity(getMaterialProperty<Real>("diffusivity"))
{
}

Real
NumbatSideFlux::computeQpIntegral()
{
  return -_porosity[_qp] * _diffusivity[_qp] * _grad_u[_qp] * _normals[_qp];
}
