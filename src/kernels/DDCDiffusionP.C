/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "DDCDiffusion.h"

template<>
InputParameters validParams<DDCDiffusion>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

DDCDiffusion::DDCDiffusion(const InputParameters & parameters) :
    Kernel(parameters),
    _porosity(getMaterialProperty<Real>("porosity")),
    _density(getMaterialProperty<Real>("density")),
    _diffusivity(getMaterialProperty<Real>("diffusivity")),
    _water_density(getMaterialProperty<Real>("water_density")),
    _solute_density(getMaterialProperty<Real>("solute_density"))
{
}

Real
DDCDiffusion::computeQpResidual()
{
  return _grad_test[_i][_qp] * _density[_qp] * _porosity[_qp] * _diffusivity[_qp] * _grad_u[_qp] *(1.0 / _solute_density[_qp] - 1.0 / _water_density[_qp]);
}

Real
DDCDiffusion::computeQpJacobian()
{
  return _grad_test[_i][_qp] * _density[_qp] * _porosity[_qp] * _diffusivity[_qp] * _grad_phi[_j][_qp] *(1.0 / _solute_density[_qp] - 1.0 / _water_density[_qp]);
}

Real
DDCDiffusion::computeQpOffDiagJacobian(unsigned int jvar)
{
  return 0.0;
}
