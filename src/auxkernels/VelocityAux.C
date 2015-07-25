/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
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
