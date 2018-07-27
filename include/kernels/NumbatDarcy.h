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
#include "JvarMapInterface.h"

class NumbatDarcy;

template <>
InputParameters validParams<NumbatDarcy>();

class NumbatDarcy : public DerivativeMaterialInterface<JvarMapKernelInterface<Kernel>>
{
public:
  NumbatDarcy(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  /// Number of coupled species
  const unsigned int _num_species;
  /// Concentration variable number(s)
  std::vector<unsigned int> _c_var;
  /// Concentration variable name(s)
  std::vector<VariableName> _c_name;
  /// Porosity
  const MaterialProperty<Real> & _porosity;
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

#endif // NUMBATDARCY_H
