/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NumbatTotalMassSF.h"

template <>
InputParameters
validParams<NumbatTotalMassSF>()
{
  InputParameters params = validParams<ElementIntegralVariablePostprocessor>();
  params.addClassDescription(
      "Calculates the total mass in model for the streamfunction formulation");
  return params;
}

NumbatTotalMassSF::NumbatTotalMassSF(const InputParameters & parameters)
  : ElementIntegralVariablePostprocessor(parameters)
{
}

Real
NumbatTotalMassSF::computeQpIntegral()
{
  return _u[_qp];
}
