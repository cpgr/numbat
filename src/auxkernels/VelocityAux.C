/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "VelocityAux.h"

template<>
InputParameters validParams<VelocityAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("streamfunction_variable", "The gradient of the streamfunction is the velocity.");
  return params;
}

VelocityAux::VelocityAux(const InputParameters & parameters) :
    AuxKernel(parameters),
    _velocity(coupledGradient("streamfunction_variable"))
{}

Real
VelocityAux::computeValue()
{
  return 1.0;
}
