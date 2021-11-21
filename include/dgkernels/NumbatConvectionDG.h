/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATCONVECTIONDG_H
#define NUMBATCONVECTIONDG_H

#include "DGKernel.h"

class NumbatConvectionDG : public DGKernel
{
public:
  NumbatConvectionDG(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type) override;
  virtual Real computeQpJacobian(Moose::DGJacobianType type) override;
  virtual Real computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar) override;

  /// Pressure variable number
  const unsigned int _pvarnum;
  /// Pressure MooseVariable
  MooseVariable & _pvar;
  /// Pressure gradient
  const VariableGradient & _grad_pressure;
  /// Pressure gradient of neighbour
  const VariableGradient & _grad_pressure_neighbor;
  /// Density
  const MaterialProperty<Real> & _density;
  /// Density of neighbour
  const MaterialProperty<Real> & _density_neighbor;
  /// Derivative of density wrt concentration
  const MaterialProperty<Real> & _ddensity_dc;
  /// Derivative of density wrt concentration of neighbour
  const MaterialProperty<Real> & _ddensity_dc_neighbor;
  /// Gravity
  RealVectorValue _gravity;
  /// Viscosity
  const MaterialProperty<Real> & _viscosity;
  /// Viscosity of neighbour
  const MaterialProperty<Real> & _viscosity_neighbor;
  /// Permeability tensor material property
  const MaterialProperty<RealTensorValue> & _permeability;
  /// Permeability tensor material property of neighbour
  const MaterialProperty<RealTensorValue> & _permeability_neighbor;
};

#endif // NUMBATCONVECTIONDG_H
