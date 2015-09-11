/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "DarcyDDC.h"

template<>
InputParameters validParams<DarcyDDC>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("gamma", 1.0, "The anisotropy ratio");
  params.addRequiredCoupledVar("concentration_variable", "The concentration variable");
  MooseEnum component("x y", "x");
  params.addParam<MooseEnum>("component", component, "The component of the streamfunction");
  return params;
}

DarcyDDC::DarcyDDC(const InputParameters & parameters) :
    Kernel(parameters),
    _gamma(getParam<Real>("gamma")),
    _grad_concentration(coupledGradient("concentration_variable")),
    _grad_concentration_var(coupled("concentration_variable")),
    _component(getParam<MooseEnum>("component"))
{
  /**
   * This kernel is only applicable in 2D or 3D. If the mesh dimension is
   * 1, throw an error
   */
  _mesh_dimension = _mesh.dimension();

  if (_mesh_dimension == 1)
    mooseError("The dimension of the mesh must be 2 or 3 to use Numbat.");

}

Real DarcyDDC::computeQpResidual()
{
  Real qpresidual;

  /// If the mesh is 2D
  if (_mesh_dimension == 2)
    qpresidual = _gamma * _test[_i][_qp] * _grad_concentration[_qp](0) - _grad_test[_i][_qp] * _grad_u[_qp];

  /// Else if the mesh is 3D
  else if (_mesh_dimension == 3)
  {
    if (_component == "x")
      qpresidual = _gamma * _test[_i][_qp] * _grad_concentration[_qp](1) - _grad_test[_i][_qp] * _grad_u[_qp];

    else if (_component == "y")
      qpresidual = - _gamma * _test[_i][_qp] * _grad_concentration[_qp](0) - _grad_test[_i][_qp] * _grad_u[_qp];
  }

  return qpresidual;
}

Real DarcyDDC::computeQpJacobian()
{
  return - _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}

Real DarcyDDC::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real qpoffdiagjacobian;

  if (jvar == _grad_concentration_var)
  {
    /// If the mesh is 2D
    if (_mesh_dimension == 2)
      qpoffdiagjacobian = _gamma * _test[_i][_qp] * _grad_phi[_j][_qp](0);

    /// Else if the mesh is 3D
    else if (_mesh_dimension == 3)
    {
      if (_component == "x")
        qpoffdiagjacobian = _gamma * _test[_i][_qp] * _grad_phi[_j][_qp](1);

      else if (_component == "y")
        qpoffdiagjacobian = - _gamma * _test[_i][_qp] * _grad_phi[_j][_qp](0);
    }
  }
  else
    qpoffdiagjacobian = 0.0;

  return qpoffdiagjacobian;
}
