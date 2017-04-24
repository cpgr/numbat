/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "ConvectionDiffusionDDC.h"

template<>
InputParameters validParams<ConvectionDiffusionDDC>()
{
  InputParameters params = validParams<Kernel>();
  RealTensorValue isotropic_tensor(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
  params.addParam<RealTensorValue>("anisotropic_tensor", isotropic_tensor, "Anisotropic coefficient tensor");
  params.addRequiredCoupledVar("streamfunction_variable", "The streamfunction variable(s)");
  return params;
}

ConvectionDiffusionDDC::ConvectionDiffusionDDC(const InputParameters & parameters) :
    Kernel(parameters),
    _gamma_tensor(getParam<RealTensorValue>("anisotropic_tensor"))
{
  // The number of streamfunction variables coupled in
  unsigned int n = coupledComponents("streamfunction_variable");

  // Check that the correct number of streamfunction variables has been supplied. There should
  // be (mesh dimension) - 1 streamfunction variables coupled in
  _mesh_dimension = _mesh.dimension();

  if (_mesh_dimension == 1)
    mooseError("Numbat only works for 2D or 3D meshes");

  if (n != _mesh_dimension - 1)
    mooseError("The number of streamfunction variables provided in " << _name << " is not correct. There should be one for a 2D mesh, and two for a 3D mesh");

  // Now fill the vectors of gradients and variable numbers with the given variables
  _grad_streamfunction.resize(n);
  _streamfunction_var.resize(n);

  for (unsigned int i = 0; i < n; ++i)
  {
    _grad_streamfunction[i] = & coupledGradient("streamfunction_variable", i);
    _streamfunction_var[i] = coupled("streamfunction_variable", i);
  }
}

Real
ConvectionDiffusionDDC::computeQpResidual()
{
  Real qpresidual = 0.0;

  // If the mesh is 2D
  if (_mesh_dimension == 2)
  {
    qpresidual += -_test[_i][_qp] * (*_grad_streamfunction[0])[_qp](1) * _grad_u[_qp](0);
    qpresidual += _test[_i][_qp] * (*_grad_streamfunction[0])[_qp](0) * _grad_u[_qp](1);
    qpresidual += (_gamma_tensor * _grad_u[_qp]) * _grad_test[_i][_qp];
  }

  // Else if the mesh is 3D
  else
  {
    qpresidual += -_test[_i][_qp] * (*_grad_streamfunction[1])[_qp](2) * _grad_u[_qp](0);
    qpresidual +=  _test[_i][_qp] * (*_grad_streamfunction[0])[_qp](2) * _grad_u[_qp](1);
    qpresidual += _test[_i][_qp] * ((*_grad_streamfunction[1])[_qp](0) - (*_grad_streamfunction[0])[_qp](1)) * _grad_u[_qp](2);
    qpresidual += (_gamma_tensor * _grad_u[_qp]) * _grad_test[_i][_qp];
  }

  return qpresidual;
}

Real
ConvectionDiffusionDDC::computeQpJacobian()
{
  Real qpjacobian = 0.0;

  // If the mesh is 2D
  if (_mesh_dimension == 2)
  {
    qpjacobian += - _test[_i][_qp] * (*_grad_streamfunction[0])[_qp](1) * _grad_phi[_j][_qp](0);
    qpjacobian += _test[_i][_qp] * (*_grad_streamfunction[0])[_qp](0) * _grad_phi[_j][_qp](1);
    qpjacobian += (_gamma_tensor * _grad_phi[_j][_qp]) * _grad_test[_i][_qp];
  }

  // Else if the mesh is 3D
  else
  {
    qpjacobian += -_test[_i][_qp] * (*_grad_streamfunction[1])[_qp](2) * _grad_phi[_j][_qp](0);
    qpjacobian +=  _test[_i][_qp] * (*_grad_streamfunction[0])[_qp](2) * _grad_phi[_j][_qp](1);
    qpjacobian += _test[_i][_qp] * ((*_grad_streamfunction[1])[_qp](0) - (*_grad_streamfunction[0])[_qp](1)) * _grad_phi[_j][_qp](2);
    qpjacobian += (_gamma_tensor * _grad_phi[_j][_qp]) * _grad_test[_i][_qp];
  }

  return qpjacobian;
}


Real
ConvectionDiffusionDDC::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real qpoffdiagjacobian = 0.;

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
      qpoffdiagjacobian +=  _test[_i][_qp] * _grad_phi[_j][_qp](2) * _grad_u[_qp](1);
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
