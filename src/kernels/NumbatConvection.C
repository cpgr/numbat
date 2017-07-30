/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatConvection.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<NumbatConvection>()
{
  InputParameters params = validParams<Kernel>();
  RealVectorValue g(0, 0, -9.81);
  params.addParam<RealVectorValue>(
      "gravity", g, "Gravity vector. Defaults to -9.81 in y direction for 2D, z direction for 3D");
  params.addRequiredCoupledVar("pressure", "Pressure variable");
  params.addClassDescription("Convection of concentration with velocity given by Darcy's law");
  return params;
}

NumbatConvection::NumbatConvection(const InputParameters & parameters)
  : Kernel(parameters),
    _grad_pressure(coupledGradient("pressure")),
    _pvar(coupled("pressure")),
    _density(getMaterialProperty<Real>("density")),
    _ddensity_dc(getMaterialProperty<Real>("ddensity_dc")),
    _gravity(getParam<RealVectorValue>("gravity")),
    _viscosity(getMaterialProperty<Real>("viscosity")),
    _permeability(getMaterialProperty<RealTensorValue>("permeability"))
{
  // Numbat only works in 2 or 3 dimensions
  if (_mesh.dimension() == 1)
    mooseError("Numbat only works for 2D or 3D meshes!");

  // If gravity hasn't been provided, use a value of -9.81 in the y direction
  // for 2D, or in the z direction for 3D (which is the default)
  if (!parameters.isParamSetByUser("gravity"))
    if (_mesh.dimension() == 2)
      _gravity = RealVectorValue(0, -9.81, 0);
}

Real
NumbatConvection::computeQpResidual()
{
  RealVectorValue velocity =
      -_permeability[_qp] / _viscosity[_qp] * (_grad_pressure[_qp] - _density[_qp] * _gravity);
  return -_u[_qp] * (velocity * _grad_test[_i][_qp]);
}

Real
NumbatConvection::computeQpJacobian()
{
  RealVectorValue velocity =
      -_permeability[_qp] / _viscosity[_qp] * (_grad_pressure[_qp] - _density[_qp] * _gravity);
  RealVectorValue dvelocity_dc =
      _permeability[_qp] / _viscosity[_qp] * _ddensity_dc[_qp] * _gravity;
  return -_phi[_j][_qp] * (velocity * _grad_test[_i][_qp]) -
         _u[_qp] * _phi[_j][_qp] * dvelocity_dc * _grad_test[_i][_qp];
}

Real
NumbatConvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _pvar)
  {
    RealVectorValue dvelocity = -_permeability[_qp] / _viscosity[_qp] * (_grad_phi[_j][_qp]);
    return -_u[_qp] * (dvelocity * _grad_test[_i][_qp]);
  }
  else
    return 0.0;
}
