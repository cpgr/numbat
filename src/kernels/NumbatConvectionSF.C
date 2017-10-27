/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatConvectionSF.h"

template <>
InputParameters
validParams<NumbatConvectionSF>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("streamfunction", "The streamfunction variable(s)");
  params.addClassDescription("Convection of concentration with velocity given by Darcy's law using "
                             "the streamfunction formulation");
  return params;
}

NumbatConvectionSF::NumbatConvectionSF(const InputParameters & parameters) : Kernel(parameters)
{
  // The number of streamfunction variables coupled in
  unsigned int n = coupledComponents("streamfunction");

  // Check that the correct number of streamfunction variables has been supplied. There should
  // be (mesh dimension) - 1 streamfunction variables coupled in
  _mesh_dimension = _mesh.dimension();

  if (_mesh_dimension == 1)
    mooseError("Numbat only works for 2D or 3D meshes");

  if (n != _mesh_dimension - 1)
    mooseError("The number of streamfunction variables provided in ",
               _name,
               " is not correct. There should be one for a 2D mesh, and two for a 3D mesh");

  // Now fill the vectors of gradients and variable numbers with the given variables
  _grad_streamfunction.resize(n);
  _streamfunction_var.resize(n);

  for (unsigned int i = 0; i < n; ++i)
  {
    _grad_streamfunction[i] = &coupledGradient("streamfunction", i);
    _streamfunction_var[i] = coupled("streamfunction", i);
  }
}

Real
NumbatConvectionSF::computeQpResidual()
{
  Real qpresidual = 0.0;

  // If the mesh is 2D
  if (_mesh_dimension == 2)
  {
    qpresidual += -_test[_i][_qp] * (*_grad_streamfunction[0])[_qp](1) * _grad_u[_qp](0);
    qpresidual += _test[_i][_qp] * (*_grad_streamfunction[0])[_qp](0) * _grad_u[_qp](1);
  }

  // Else if the mesh is 3D
  else
  {
    qpresidual += -_test[_i][_qp] * (*_grad_streamfunction[1])[_qp](2) * _grad_u[_qp](0);
    qpresidual += _test[_i][_qp] * (*_grad_streamfunction[0])[_qp](2) * _grad_u[_qp](1);
    qpresidual += _test[_i][_qp] *
                  ((*_grad_streamfunction[1])[_qp](0) - (*_grad_streamfunction[0])[_qp](1)) *
                  _grad_u[_qp](2);
  }

  return qpresidual;
}

Real
NumbatConvectionSF::computeQpJacobian()
{
  Real qpjacobian = 0.0;

  // If the mesh is 2D
  if (_mesh_dimension == 2)
  {
    qpjacobian += -_test[_i][_qp] * (*_grad_streamfunction[0])[_qp](1) * _grad_phi[_j][_qp](0);
    qpjacobian += _test[_i][_qp] * (*_grad_streamfunction[0])[_qp](0) * _grad_phi[_j][_qp](1);
  }

  // Else if the mesh is 3D
  else
  {
    qpjacobian += -_test[_i][_qp] * (*_grad_streamfunction[1])[_qp](2) * _grad_phi[_j][_qp](0);
    qpjacobian += _test[_i][_qp] * (*_grad_streamfunction[0])[_qp](2) * _grad_phi[_j][_qp](1);
    qpjacobian += _test[_i][_qp] *
                  ((*_grad_streamfunction[1])[_qp](0) - (*_grad_streamfunction[0])[_qp](1)) *
                  _grad_phi[_j][_qp](2);
  }

  return qpjacobian;
}

Real
NumbatConvectionSF::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real qpoffdiagjacobian = 0.0;

  // If the mesh is 2D
  if (_mesh_dimension == 2)
  {
    if (jvar == _streamfunction_var[0])
    {
      qpoffdiagjacobian += -_test[_i][_qp] * _grad_phi[_j][_qp](1) * _grad_u[_qp](0);
      qpoffdiagjacobian += _test[_i][_qp] * _grad_phi[_j][_qp](0) * _grad_u[_qp](1);
    }
  }

  // Else if the mesh is 3D
  else
  {
    if (jvar == _streamfunction_var[0])
    {
      qpoffdiagjacobian += _test[_i][_qp] * _grad_phi[_j][_qp](2) * _grad_u[_qp](1);
      qpoffdiagjacobian += -_test[_i][_qp] * _grad_phi[_j][_qp](1) * _grad_u[_qp](2);
    }
    else if (jvar == _streamfunction_var[1])
    {
      qpoffdiagjacobian += -_test[_i][_qp] * _grad_phi[_j][_qp](2) * _grad_u[_qp](0);
      qpoffdiagjacobian += _test[_i][_qp] * _grad_phi[_j][_qp](0) * _grad_u[_qp](2);
    }
  }

  return qpoffdiagjacobian;
}
