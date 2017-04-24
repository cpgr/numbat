/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "VelocityDDCAux.h"

template<>
InputParameters validParams<VelocityDDCAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("streamfunction_variable", "The streamfunction variable(s)");
  MooseEnum component("x y z", "x");
  params.addParam<MooseEnum>("component", component, "The component of the velocity");
  return params;
}

VelocityDDCAux::VelocityDDCAux(const InputParameters & parameters) :
    AuxKernel(parameters),
    _component(getParam<MooseEnum>("component"))
{
  /// The number of streamfunction variables coupled in
  unsigned int n = coupledComponents("streamfunction_variable");

  /// Check that the correct number of streamfunction variables has been supplied. There should
  /// be (mesh dimension) - 1 streamfunction variables coupled in
  _mesh_dimension = _mesh.dimension();

  if (_mesh_dimension == 1)
    mooseError("The dimension of the mesh must be 2 or 3 to use Numbat.");

  if (n != _mesh_dimension - 1)
    mooseError("The number of streamfunction variables provided in ", _name, " is not correct. There should be one for a 2D mesh, and 2 two for a 3D mesh");

  /// Now fill the vector of gradients with the given variables
  _grad_streamfunction.resize(n);

  for (unsigned int i = 0; i < n; ++i)
    _grad_streamfunction[i] = &coupledGradient("streamfunction_variable", i);
}

Real
VelocityDDCAux::computeValue()
{
  Real vel = 0.;

  /**
   * If the mesh is 2D, the velocity components (u, w) are given by
   * (- (d psi)/(dy), (d psi)/(dx)).
   */
  if (_mesh_dimension == 2)
  {
    if (_component == "x")
      vel = - (*_grad_streamfunction[0])[_qp](1);
    else if (_component == "y")
      vel = (*_grad_streamfunction[0])[_qp](0);
  }
  /**
   * If the mesh is 3D, the velocity components (u, v, w) are given by
   * curl(Psi)
   */
   else if (_mesh_dimension == 3)
   {
     if (_component == "x")
       vel = - (*_grad_streamfunction[1])[_qp](2);
     else if (_component == "y")
       vel = (*_grad_streamfunction[0])[_qp](2);
     else if (_component == "z")
       vel = (*_grad_streamfunction[1])[_qp](0) - (*_grad_streamfunction[0])[_qp](1);
   }

  return vel;
}
