/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatDiffusionDGBC.h"

#include "MooseVariable.h"
#include "libmesh/utility.h"

registerMooseObject("NumbatApp", NumbatDiffusionDGBC);

InputParameters
NumbatDiffusionDGBC::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addRequiredParam<Real>("value", "Average value of the boundary condition");
  params.addParam<Real>("epsilon", -1, "epsilon");
  params.addParam<Real>("sigma", 6, "sigma");
  params.addClassDescription("Dirichlet boundary condition for use with NumbatDiffusionDG");
  return params;
}

NumbatDiffusionDGBC::NumbatDiffusionDGBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _value(getParam<Real>("value")),
    _epsilon(getParam<Real>("epsilon")),
    _sigma(getParam<Real>("sigma")),
    _porosity(getMaterialProperty<Real>("porosity")),
    _diffusivity(getMaterialProperty<Real>("diffusivity"))
{
}

Real
NumbatDiffusionDGBC::computeQpResidual()
{
  const unsigned int elem_b_order = _var.order();
  const double h_elem =
      _current_elem->volume() / _current_side_elem->volume() * 1.0 / Utility::pow<2>(elem_b_order);

  Real r = 0;
  r -= (_porosity[_qp] * _diffusivity[_qp] * _grad_u[_qp] * _normals[_qp] * _test[_i][_qp]);
  r += _epsilon * (_u[_qp] - _value) * _porosity[_qp] * _diffusivity[_qp] * _grad_test[_i][_qp] *
       _normals[_qp];
  r += _sigma / h_elem * (_u[_qp] - _value) * _test[_i][_qp];

  return r;
}

Real
NumbatDiffusionDGBC::computeQpJacobian()
{
  const unsigned int elem_b_order = _var.order();
  const double h_elem =
      _current_elem->volume() / _current_side_elem->volume() * 1.0 / Utility::pow<2>(elem_b_order);

  Real r = 0;
  r -= (_porosity[_qp] * _diffusivity[_qp] * _grad_phi[_j][_qp] * _normals[_qp] * _test[_i][_qp]);
  r += _epsilon * _phi[_j][_qp] * _porosity[_qp] * _diffusivity[_qp] * _grad_test[_i][_qp] *
       _normals[_qp];
  r += _sigma / h_elem * _phi[_j][_qp] * _test[_i][_qp];

  return r;
}
