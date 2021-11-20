/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatTimeDerivative.h"
#include "MooseMesh.h"

registerMooseObject("NumbatApp", NumbatTimeDerivative);

InputParameters
NumbatTimeDerivative::validParams()
{
  InputParameters params = TimeDerivative::validParams();
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
