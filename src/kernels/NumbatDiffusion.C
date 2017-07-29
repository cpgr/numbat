/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatDiffusion.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<NumbatDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addClassDescription("Diffusion kernel with anisotropy and porosity");
  return params;
}

NumbatDiffusion::NumbatDiffusion(const InputParameters & parameters)
  : Diffusion(parameters),
    _porosity(getMaterialProperty<Real>("porosity")),
    _diffusivity(getMaterialProperty<Real>("diffusivity"))
{
  // Numbat only works in 2 or 3 dimensions
  if (_mesh.dimension() == 1)
    mooseError("Numbat only works for 2D or 3D meshes!");
}

Real
NumbatDiffusion::computeQpResidual()
{
  return _porosity[_qp] * _diffusivity[_qp] * Diffusion::computeQpResidual();
}

Real
NumbatDiffusion::computeQpJacobian()
{
  return _porosity[_qp] * _diffusivity[_qp] * Diffusion::computeQpJacobian();
}
