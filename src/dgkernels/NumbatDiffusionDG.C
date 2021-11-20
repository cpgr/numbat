/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatDiffusionDG.h"

#include "MooseVariable.h"
#include "MooseMesh.h"
#include "libmesh/utility.h"

registerMooseObject("NumbatApp", NumbatDiffusionDG);

InputParameters
NumbatDiffusionDG::validParams()
{
  InputParameters params = DGKernel::validParams();
  params.addParam<Real>("epsilon", -1, "epsilon");
  params.addParam<Real>("sigma", 6, "sigma");
  params.addClassDescription("Diffusion kernel for the Discontinuous Galerkin method");
  return params;
}

NumbatDiffusionDG::NumbatDiffusionDG(const InputParameters & parameters)
  : DGKernel(parameters),
    _epsilon(getParam<Real>("epsilon")),
    _sigma(getParam<Real>("sigma")),
    _porosity(getMaterialProperty<Real>("porosity")),
    _porosity_neighbor(getNeighborMaterialProperty<Real>("porosity")),
    _diffusivity(getMaterialProperty<Real>("diffusivity")),
    _diffusivity_neighbor(getNeighborMaterialProperty<Real>("diffusivity"))
{
  // Numbat only works in 2 or 3 dimensions
  if (_mesh.dimension() == 1)
    mooseError("Numbat only works for 2D or 3D meshes!");
}

Real
NumbatDiffusionDG::computeQpResidual(Moose::DGResidualType type)
{
  Real residual = 0.0;

  const unsigned int elem_b_order = _var.order();
  const double h_elem =
      _current_elem->volume() / _current_side_elem->volume() * 1.0 / Utility::pow<2>(elem_b_order);

  switch (type)
  {
    case Moose::Element:
      residual -= 0.5 *
                  (_porosity[_qp] * _diffusivity[_qp] * _grad_u[_qp] * _normals[_qp] +
                   _porosity_neighbor[_qp] * _diffusivity_neighbor[_qp] * _grad_u_neighbor[_qp] *
                       _normals[_qp]) *
                  _test[_i][_qp];
      residual += _epsilon * 0.5 * (_u[_qp] - _u_neighbor[_qp]) * _porosity[_qp] *
                  _diffusivity[_qp] * _grad_test[_i][_qp] * _normals[_qp];
      residual += _sigma / h_elem * (_u[_qp] - _u_neighbor[_qp]) * _test[_i][_qp];
      break;

    case Moose::Neighbor:
      residual += 0.5 *
                  (_porosity[_qp] * _diffusivity[_qp] * _grad_u[_qp] * _normals[_qp] +
                   _porosity_neighbor[_qp] * _diffusivity_neighbor[_qp] * _grad_u_neighbor[_qp] *
                       _normals[_qp]) *
                  _test_neighbor[_i][_qp];
      residual += _epsilon * 0.5 * (_u[_qp] - _u_neighbor[_qp]) * _porosity_neighbor[_qp] *
                  _diffusivity_neighbor[_qp] * _grad_test_neighbor[_i][_qp] * _normals[_qp];
      residual -= _sigma / h_elem * (_u[_qp] - _u_neighbor[_qp]) * _test_neighbor[_i][_qp];
      break;
  }

  return residual;
}

Real
NumbatDiffusionDG::computeQpJacobian(Moose::DGJacobianType type)
{
  Real jacobian = 0.0;

  const unsigned int elem_b_order = _var.order();
  const double h_elem =
      _current_elem->volume() / _current_side_elem->volume() * 1. / Utility::pow<2>(elem_b_order);

  switch (type)
  {
    case Moose::ElementElement:
      jacobian -= 0.5 * _porosity[_qp] * _diffusivity[_qp] * _grad_phi[_j][_qp] * _normals[_qp] *
                  _test[_i][_qp];
      jacobian += _epsilon * 0.5 * _phi[_j][_qp] * _porosity[_qp] * _diffusivity[_qp] *
                  _grad_test[_i][_qp] * _normals[_qp];
      jacobian += _sigma / h_elem * _phi[_j][_qp] * _test[_i][_qp];
      break;

    case Moose::ElementNeighbor:
      jacobian -= 0.5 * _porosity_neighbor[_qp] * _diffusivity_neighbor[_qp] *
                  _grad_phi_neighbor[_j][_qp] * _normals[_qp] * _test[_i][_qp];
      jacobian -= _epsilon * 0.5 * _phi_neighbor[_j][_qp] * _porosity[_qp] * _diffusivity[_qp] *
                  _grad_test[_i][_qp] * _normals[_qp];
      jacobian -= _sigma / h_elem * _phi_neighbor[_j][_qp] * _test[_i][_qp];
      break;

    case Moose::NeighborElement:
      jacobian += 0.5 * _porosity[_qp] * _diffusivity[_qp] * _grad_phi[_j][_qp] * _normals[_qp] *
                  _test_neighbor[_i][_qp];
      jacobian += _epsilon * 0.5 * _phi[_j][_qp] * _porosity_neighbor[_qp] *
                  _diffusivity_neighbor[_qp] * _grad_test_neighbor[_i][_qp] * _normals[_qp];
      jacobian -= _sigma / h_elem * _phi[_j][_qp] * _test_neighbor[_i][_qp];
      break;

    case Moose::NeighborNeighbor:
      jacobian += 0.5 * _porosity_neighbor[_qp] * _diffusivity_neighbor[_qp] *
                  _grad_phi_neighbor[_j][_qp] * _normals[_qp] * _test_neighbor[_i][_qp];
      jacobian -= _epsilon * 0.5 * _phi_neighbor[_j][_qp] * _porosity_neighbor[_qp] *
                  _diffusivity_neighbor[_qp] * _grad_test_neighbor[_i][_qp] * _normals[_qp];
      jacobian += _sigma / h_elem * _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
      break;
  }

  return jacobian;
}
