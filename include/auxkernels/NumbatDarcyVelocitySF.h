/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATDARCYVELOCITYSF_H
#define NUMBATDARCYVELOCITYSF_H

#include "AuxKernel.h"
#include "MooseMesh.h"

class NumbatDarcyVelocitySF;

template <>
InputParameters validParams<NumbatDarcyVelocitySF>();

class NumbatDarcyVelocitySF : public AuxKernel
{
public:
  NumbatDarcyVelocitySF(const InputParameters & parameters);

protected:
  virtual Real computeValue();

private:
  /// The gradient of the streamfunction variable(s)
  std::vector<const VariableGradient *> _grad_streamfunction;
  /// The component of the velocity
  const MooseEnum & _component;
  /// The mesh dimension
  unsigned int _mesh_dimension;
};

#endif // NUMBATDARCYVELOCITYSF_H
