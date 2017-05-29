/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NumbatConvection.h"

template <>
InputParameters
validParams<NumbatConvection>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("concentration", "Concentration variable");
  params.addRequiredParam<Real>("viscosity", "Fluid viscosity");
  params.addRequiredParam<RealTensorValue>("permeability", "Permeability tensor");
  params.addRequiredParam<RealVectorValue>("gravity", "Gravity vector");
  params.addRequiredCoupledVar("pressure", "Pressure variable");
  params.addClassDescription("Convection of concentration with velocity given by Darcy's law");
  return params;
}

NumbatConvection::NumbatConvection(const InputParameters & parameters)
  : Kernel(parameters),
    _concentration(coupledValue("concentration")),
    _grad_pressure(coupledGradient("pressure")),
    _pvar(coupled("pressure")),
    _porosity(getMaterialProperty<Real>("porosity")),
    _density(getMaterialProperty<Real>("density")),
    _gravity(getParam<RealVectorValue>("gravity")),
    _viscosity(getParam<Real>("viscosity")),
    _permeability(getParam<RealTensorValue>("permeability"))
{
}

Real
NumbatConvection::computeQpResidual()
{
  RealVectorValue velocity =
      -_permeability / _viscosity * (_grad_pressure[_qp] + _density[_qp] * _gravity);
  return -_concentration[_qp] * (velocity * _grad_test[_i][_qp]);
}

Real
NumbatConvection::computeQpJacobian()
{
  RealVectorValue velocity =
      -_permeability / _viscosity * (_grad_pressure[_qp] + _density[_qp] * _gravity);
  return -_phi[_j][_qp] * (velocity * _grad_test[_i][_qp]);
}

Real
NumbatConvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _pvar)
  {
    RealVectorValue dvelocity = -_permeability / _viscosity * (_grad_phi[_j][_qp]);
    return -_concentration[_qp] * (dvelocity * _grad_test[_i][_qp]);
  }
  else
  {
    return 0.0;
  }
}
