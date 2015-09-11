/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
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
