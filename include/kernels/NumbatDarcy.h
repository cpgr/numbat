/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATDARCY_H
#define NUMBATDARCY_H

#include "DerivativeMaterialInterface.h"
#include "Kernel.h"

class NumbatDarcy;

template <>
InputParameters validParams<NumbatDarcy>();

class NumbatDarcy : public DerivativeMaterialInterface<Kernel>
{
public:
  NumbatDarcy(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  /// Concentration variable name
  const VariableName _concentration_name;
  /// Concentration variable number
  const unsigned int _c_var;
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
  /// Permeability tensor
  const RealTensorValue _permeability;
};

#endif // NUMBATDARCY_H
