/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "DDCDiffusionP.h"

template<>
InputParameters validParams<DDCDiffusionP>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("solute_mass_fraction_variable", "The solute mass fraction variable");
  return params;
}

DDCDiffusionP::DDCDiffusionP(const InputParameters & parameters) :
  Kernel(parameters),
  _porosity(getMaterialProperty<Real>("porosity")),
  _density(getMaterialProperty<Real>("density")),
  _diffusivity(getMaterialProperty<Real>("diffusivity")),
  _water_density(getMaterialProperty<Real>("water_density")),
  _solute_density(getMaterialProperty<Real>("solute_density")),
  _grad_solute_mass_fraction(coupledGradient("solute_mass_fraction_variable")),
  _xvar(coupled("solute_mass_fraction_variable"))
{
}

Real
DDCDiffusionP::computeQpResidual()
{
  return _grad_test[_i][_qp] * _density[_qp] * _porosity[_qp] * _diffusivity[_qp] * _grad_solute_mass_fraction[_qp] *(1.0 / _solute_density[_qp] - 1.0 / _water_density[_qp]);
}

Real
DDCDiffusionP::computeQpJacobian()
{
  return 0.0;
}

Real
DDCDiffusionP::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real qpoffdiagjacobian = 0.0;

  if (jvar == _xvar)
  { 
    /// Derivative wrt solute mass fraction
    qpoffdiagjacobian = _grad_test[_i][_qp] * _density[_qp] * _porosity[_qp] * _diffusivity[_qp] * _grad_phi[_j][_qp] *(1.0 / _solute_density[_qp] - 1.0 / _water_density[_qp]);
  }

  return qpoffdiagjacobian;
}
