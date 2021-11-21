/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatDarcyVelocitySF.h"

registerMooseObject("NumbatApp", NumbatDarcyVelocitySF);

InputParameters
NumbatDarcyVelocitySF::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("streamfunction", "The streamfunction variable(s)");
  MooseEnum component("x y z", "x");
  params.addParam<MooseEnum>("component", component, "The component of the velocity");
  params.addClassDescription("Calculates Darcy velocity");
  return params;
}

NumbatDarcyVelocitySF::NumbatDarcyVelocitySF(const InputParameters & parameters)
  : AuxKernel(parameters), _component(getParam<MooseEnum>("component"))
{
  // The number of streamfunction variables coupled in
  unsigned int n = coupledComponents("streamfunction");

  // Check that the correct number of streamfunction variables has been supplied. There should
  // be (mesh dimension) - 1 streamfunction variables coupled in
  _mesh_dimension = _mesh.dimension();

  if (_mesh_dimension == 1)
    mooseError("The dimension of the mesh must be 2 or 3 to use Numbat.");

  if (n != _mesh_dimension - 1)
    mooseError("The number of streamfunction variables provided in ",
               _name,
               " is not correct. There should be one for a 2D mesh, and 2 two for a 3D mesh");

  // Now fill the vector of gradients with the given variables
  _grad_streamfunction.resize(n);

  for (unsigned int i = 0; i < n; ++i)
    _grad_streamfunction[i] = &coupledGradient("streamfunction", i);
}

Real
NumbatDarcyVelocitySF::computeValue()
{
  Real vel = 0.;

  // If the mesh is 2D, the velocity components (u, w) are given by
  // (- (d psi)/(dy), (d psi)/(dx)).
  if (_mesh_dimension == 2)
  {
    if (_component == "x")
      vel = -(*_grad_streamfunction[0])[_qp](1);
    else if (_component == "y")
      vel = (*_grad_streamfunction[0])[_qp](0);
  }
  // If the mesh is 3D, the velocity components (u, v, w) are given by
  // curl(Psi)
  else if (_mesh_dimension == 3)
  {
    if (_component == "x")
      vel = -(*_grad_streamfunction[1])[_qp](2);
    else if (_component == "y")
      vel = (*_grad_streamfunction[0])[_qp](2);
    else if (_component == "z")
      vel = (*_grad_streamfunction[1])[_qp](0) - (*_grad_streamfunction[0])[_qp](1);
  }

  return vel;
}
