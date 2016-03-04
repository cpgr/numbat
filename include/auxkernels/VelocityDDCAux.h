/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef VELOCITYDDCAUX_H
#define VELOCITYDDCAUX_H

#include "AuxKernel.h"
#include "MooseMesh.h"

class VelocityDDCAux;

template<>
InputParameters validParams<VelocityDDCAux>();

class VelocityDDCAux : public AuxKernel
{
public:

  VelocityDDCAux(const InputParameters & parameters);

protected:

  virtual Real computeValue();

private:
  /// The gradient of the streamfunction variable(s)
  std::vector<const VariableGradient *>  _grad_streamfunction;
  /// The component of the velocity
  const MooseEnum & _component;
  /// The mesh dimension
  unsigned int _mesh_dimension;
};

#endif //VELOCITYDDCAUX_H
