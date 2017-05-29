/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NumbatConvection.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<NumbatConvection>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("viscosity", "Fluid viscosity");
  params.addRequiredParam<RealTensorValue>("permeability", "Permeability tensor");
  params.addRequiredParam<RealVectorValue>("gravity", "Gravity vector");
  params.addRequiredCoupledVar("pressure", "Pressure variable");
  params.addClassDescription("Convection of concentration with velocity given by Darcy's law");
  return params;
}

NumbatConvection::NumbatConvection(const InputParameters & parameters)
  : DerivativeMaterialInterface<Kernel>(parameters),
    _concentration_name(_var.name()),
    _grad_pressure(coupledGradient("pressure")),
    _pvar(coupled("pressure")),
    _porosity(getMaterialProperty<Real>("porosity")),
    _density(getMaterialProperty<Real>("density")),
    _ddensity_dc(getMaterialPropertyDerivative<Real>("density", _concentration_name)),
    _gravity(getParam<RealVectorValue>("gravity")),
    _viscosity(getParam<Real>("viscosity")),
    _permeability(getParam<RealTensorValue>("permeability"))
{
  // Numbat only works in 2 or 3 dimensions
  if (_mesh.dimension() == 1)
    mooseError("Numbat only works for 2D or 3D meshes!");
}

Real
NumbatConvection::computeQpResidual()
{
  RealVectorValue velocity =
      -_permeability / _viscosity * (_grad_pressure[_qp] + _density[_qp] * _gravity);
  return -_u[_qp] * (velocity * _grad_test[_i][_qp]);
}

Real
NumbatConvection::computeQpJacobian()
{
  RealVectorValue velocity =
      -_permeability / _viscosity * (_grad_pressure[_qp] + _density[_qp] * _gravity);
  RealVectorValue dvelocity_dc = -_permeability / _viscosity * _ddensity_dc[_qp] * _gravity;
  return -_phi[_j][_qp] * (velocity * _grad_test[_i][_qp]) -
         _u[_qp] * _phi[_j][_qp] * dvelocity_dc * _grad_test[_i][_qp];
}

Real
NumbatConvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _pvar)
  {
    RealVectorValue dvelocity = -_permeability / _viscosity * (_grad_phi[_j][_qp]);
    return -_u[_qp] * (dvelocity * _grad_test[_i][_qp]);
  }
  else
  {
    return 0.0;
  }
}
