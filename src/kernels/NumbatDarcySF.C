/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatDarcySF.h"

registerMooseObject("NumbatApp", NumbatDarcySF);

template <>
InputParameters
validParams<NumbatDarcySF>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("gamma", 1.0, "The anisotropy ratio");
  params.addRequiredCoupledVar("concentration", "The concentration variable");
  MooseEnum component("x=0 y=1", "x");
  params.addParam<MooseEnum>("component", component, "The component of the streamfunction");
  params.addClassDescription("Darcy's law for the streamfunction formulation");
  return params;
}

NumbatDarcySF::NumbatDarcySF(const InputParameters & parameters)
  : Kernel(parameters),
    _gamma(getParam<Real>("gamma")),
    _grad_concentration(coupledGradient("concentration")),
    _grad_concentration_var(coupled("concentration")),
    _component(getParam<MooseEnum>("component"))
{
  // This kernel is only applicable in 2D or 3D. If the mesh dimension is
  // 1, throw an error
  _mesh_dimension = _mesh.dimension();

  if (_mesh_dimension == 1)
    mooseError("Numbat only works for 2D or 3D meshes");
}

Real
NumbatDarcySF::computeQpResidual()
{
  unsigned int comp = 0;
  int sgn = 1;

  // If the mesh is 2D, comp = 0. Also, if the mesh is 3D, comp is 0 if _component = y.
  // So the only time to change it is when the mesh is 3D and _component = x
  if (_mesh_dimension == 3)
  {
    if (_component == 0)
    {
      sgn = -1;
      comp = 1;
    }
  }

  return sgn * _gamma * _test[_i][_qp] * _grad_concentration[_qp](comp) -
         _grad_test[_i][_qp] * _grad_u[_qp];
}

Real
NumbatDarcySF::computeQpJacobian()
{
  return -_grad_test[_i][_qp] * _grad_phi[_j][_qp];
}

Real
NumbatDarcySF::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _grad_concentration_var)
  {
    unsigned int comp = 0;
    int sgn = 1;

    // If the mesh is 2D, comp = 0. Also, if the mesh is 3D, comp is 0 if _component = y.
    // So the only time to change it is when the mesh is 3D and _component = x
    if (_mesh_dimension == 3)
    {
      if (_component == 0)
      {
        sgn = -1;
        comp = 1;
      }
    }
    return sgn * _gamma * _test[_i][_qp] * _grad_phi[_j][_qp](comp);
  }
  return 0.0;
}
