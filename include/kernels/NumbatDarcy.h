/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATDARCY_H
#define NUMBATDARCY_H

#include "Kernel.h"
#include "DerivativeMaterialInterface.h"

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
  /// Concentration variable number
  const unsigned int _c_var;
  /// Concentration variable name
  const VariableName _c_name;
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

#endif // NUMBATDARCY_H
