/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NumbatSideFluxSF.h"

template <>
InputParameters
validParams<NumbatSideFluxSF>()
{
  InputParameters params = validParams<SideIntegralVariablePostprocessor>();
  params.addClassDescription(
      "Calculates the flux over the boundary for the streamfunction formulation");
  return params;
}

NumbatSideFluxSF::NumbatSideFluxSF(const InputParameters & parameters)
  : SideIntegralVariablePostprocessor(parameters)
{
}

Real
NumbatSideFluxSF::computeQpIntegral()
{
  return -_grad_u[_qp] * _normals[_qp];
}
