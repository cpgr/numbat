/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATCONVECTION_H
#define NUMBATCONVECTION_H

#include "Kernel.h"
#include "DerivativeMaterialInterface.h"
#include "JvarMapInterface.h"

class NumbatConvection;

template <>
InputParameters validParams<NumbatConvection>();

class NumbatConvection : public DerivativeMaterialInterface<JvarMapKernelInterface<Kernel>>
{
public:
  NumbatConvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  /// Pressure gradient
  const VariableGradient & _grad_pressure;
  /// Pressure variable number
  const unsigned int _pvar;
  /// Density
  const MaterialProperty<Real> & _density;
  /// Derivative of density wrt concentration(s)
  std::vector<const MaterialProperty<Real> *> _ddensity_dc;
  /// Gravity
  RealVectorValue _gravity;
  /// Viscosity
  const MaterialProperty<Real> & _viscosity;
  /// Permeability tensor material property
  const MaterialProperty<RealTensorValue> & _permeability;
};

#endif // NUMBATCONVECTION_H
