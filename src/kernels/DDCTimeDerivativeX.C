/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "DDCTimeDerivativeX.h"

template<>
InputParameters validParams<DDCTimeDerivativeX>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addRequiredCoupledVar("density", "The fluid density auxillary variable");
  return params;
}

DDCTimeDerivativeX::DDCTimeDerivativeX(const InputParameters & parameters) :
    TimeDerivative(parameters),
    _porosity(getMaterialProperty<Real>("porosity")),
    _density(coupledValue("density")),
    _density_dot(coupledDot("density"))

{
}

Real
DDCTimeDerivativeX::computeQpResidual()
{
  _console << "_density_dot " << _density_dot[_qp] << std::endl;
  return _test[_i][_qp] * _porosity[_qp] * (_density[_qp] * _u_dot[_qp] + _density_dot[_qp] * _u[_qp]);
}

Real
DDCTimeDerivativeX::computeQpJacobian()
{
  return _test[_i][_qp] * _porosity[_qp] * _phi[_j][_qp] * (_density[_qp] * _du_dot_du[_qp] + _density_dot[_qp]);
}
