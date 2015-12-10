/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "DDCDensityAux.h"

template<>
InputParameters validParams<DDCDensityAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<Real>("water_density", "The density of the resident fluid");
  params.addRequiredParam<Real>("solute_density", "The density of aqueous phase solute");
  params.addRequiredCoupledVar("solute_mass_fraction_variable", "The solute mass fraction variable");
  return params;
}

DDCDensityAux::DDCDensityAux(const InputParameters & parameters) :
    AuxKernel(parameters),
    _water_density(getParam<Real>("water_density")),
    _solute_density(getParam<Real>("solute_density")),
    _solute_mass_fraction(coupledValue("solute_mass_fraction_variable"))
{
}

Real
DDCDensityAux::computeValue()
{
  return 1.0 / (_solute_mass_fraction[_qp] / _solute_density +
    (1.0 - _solute_mass_fraction[_qp]) / _water_density);;
}
