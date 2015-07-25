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

#ifndef VELOCITYAUX_H
#define VELOCITYAUX_H

#include "AuxKernel.h"

class VelocityAux;

template<>
InputParameters validParams<VelocityAux>();

class VelocityAux : public AuxKernel
{
public:

  VelocityAux(const InputParameters & parameters);

protected:

  virtual Real computeValue();

private:

  VariableGradient & _velocity;
};

#endif //VELOCITYAUX_H
