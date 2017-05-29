/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NumbatDarcy.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<NumbatDarcy>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("viscosity", "Fluid viscosity");
  params.addRequiredParam<RealTensorValue>("permeability", "Permeability tensor");
  params.addRequiredParam<RealVectorValue>("gravity", "Gravity vector");
  params.addRequiredCoupledVar("concentration", "Concentration variable");
  params.addClassDescription("Darcy's law");
  return params;
}

NumbatDarcy::NumbatDarcy(const InputParameters & parameters)
  : DerivativeMaterialInterface<Kernel>(parameters),
    _concentration_name(getVar("concentration", 0)->name()),
    _c_var(coupled("concentration")),
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
NumbatDarcy::computeQpResidual()
{
  return _grad_test[_i][_qp] *
         (_permeability / _viscosity * (_grad_u[_qp] + _density[_qp] * _gravity));
}

Real
NumbatDarcy::computeQpJacobian()
{
  return _grad_test[_i][_qp] * (_permeability / _viscosity * _grad_phi[_j][_qp]);
}

Real
NumbatDarcy::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _c_var)
  {
    return _grad_test[_i][_qp] *
           (_permeability / _viscosity * _phi[_j][_qp] * _ddensity_dc[_qp] * _gravity);
  }
  else
    return 0.0;
}
