/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATCONVECTIONDG_H
#define NUMBATCONVECTIONDG_H

#include "DGKernel.h"
#include "DerivativeMaterialInterface.h"

class NumbatConvectionDG;

template <>
InputParameters validParams<NumbatConvectionDG>();

class NumbatConvectionDG : public DerivativeMaterialInterface<DGKernel>
{
public:
  NumbatConvectionDG(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type) override;
  virtual Real computeQpJacobian(Moose::DGJacobianType type) override;
  virtual Real computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned int jvar) override;

  /// Concentration variable name
  const VariableName _concentration_name;
  /// Pressure gradient
  const VariableGradient & _grad_pressure;
  /// Pressure variable number
  const unsigned int _pvar;
  /// Porosity
  const MaterialProperty<Real> & _porosity;
  /// Density
  const MaterialProperty<Real> & _density;
  /// Derivative of density wrt concentration
  const MaterialProperty<Real> & _ddensity_dc;
  /// Gravity
  RealVectorValue _gravity;
  /// Viscosity
  const MaterialProperty<Real> & _viscosity;
  /// Permeability tensor material property
  const MaterialProperty<RealTensorValue> & _permeability;
};

#endif // NUMBATCONVECTIONDG_H
