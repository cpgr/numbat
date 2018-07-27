/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatDarcy.h"
#include "MooseMesh.h"

registerMooseObject("NumbatApp", NumbatDarcy);

template <>
InputParameters
validParams<NumbatDarcy>()
{
  InputParameters params = validParams<Kernel>();
  RealVectorValue g(0, 0, -9.81);
  params.addParam<RealVectorValue>(
      "gravity", g, "Gravity vector. Defaults to -9.81 in y direction for 2D, z direction for 3D");
  params.addRequiredCoupledVar("concentration", "Concentration variable(s)");
  params.addClassDescription("Darcy's law");
  return params;
}

NumbatDarcy::NumbatDarcy(const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapKernelInterface<Kernel>>(parameters),
    _num_species(coupledComponents("concentration")),
    _c_var(_num_species),
    _c_name(_num_species),
    _porosity(getMaterialProperty<Real>("porosity")),
    _density(getMaterialProperty<Real>("density")),
    _ddensity_dc(_num_species),
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

  // Get derivatives of density wrt concentration
  for (unsigned int i = 0; i < _num_species; ++i)
  {
    _c_var[i] = coupled("concentration", i);
    _c_name[i] = getVar("concentration", i)->name();
    _ddensity_dc[i] = &getMaterialPropertyDerivative<Real>("density", _c_name[i]);
  }
}

Real
NumbatDarcy::computeQpResidual()
{
  return _grad_test[_i][_qp] *
         (_permeability[_qp] / _viscosity[_qp] * (_grad_u[_qp] - _density[_qp] * _gravity));
}

Real
NumbatDarcy::computeQpJacobian()
{
  return _grad_test[_i][_qp] * (_permeability[_qp] / _viscosity[_qp] * _grad_phi[_j][_qp]);
}

Real
NumbatDarcy::computeQpOffDiagJacobian(unsigned int jvar)
{
  const unsigned int cvar = mapJvarToCvar(_var.number());

  if (jvar == cvar)
  {
    return -_grad_test[_i][_qp] * (_permeability[_qp] / _viscosity[_qp] * _phi[_j][_qp] *
                                   (*_ddensity_dc[cvar])[_qp] * _gravity);
  }
  else
    return 0.0;
}
