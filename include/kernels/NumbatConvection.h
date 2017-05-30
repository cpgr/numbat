/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATCONVECTION_H
#define NUMBATCONVECTION_H

#include "DerivativeMaterialInterface.h"
#include "Kernel.h"

class NumbatConvection;

template <>
InputParameters validParams<NumbatConvection>();

class NumbatConvection : public DerivativeMaterialInterface<Kernel>
{
public:
  NumbatConvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
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
  const RealVectorValue _gravity;
  /// Viscosity
  const Real _viscosity;
  /// Permeability tensor material property
  const MaterialProperty<RealTensorValue> & _permeability;
};

#endif // NUMBATCONVECTION_H
