/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NumbatTimeDerivative.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<NumbatTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addClassDescription("Time derivative kernel");
  return params;
}

NumbatTimeDerivative::NumbatTimeDerivative(const InputParameters & parameters)
  : TimeDerivative(parameters), _porosity(getMaterialProperty<Real>("porosity"))
{
  // Numbat only works in 2 or 3 dimensions
  if (_mesh.dimension() == 1)
    mooseError("Numbat only works for 2D or 3D meshes!");
}

Real
NumbatTimeDerivative::computeQpResidual()
{
  return _porosity[_qp] * TimeDerivative::computeQpResidual();
}

Real
NumbatTimeDerivative::computeQpJacobian()
{
  return _porosity[_qp] * TimeDerivative::computeQpJacobian();
}

Real
NumbatTimeDerivative::computeQpOffDiagJacobian(unsigned int /*jvar*/)
{
  return 0.0;
}
