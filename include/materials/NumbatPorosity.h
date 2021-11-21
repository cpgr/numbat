/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATPOROSITY_H
#define NUMBATPOROSITY_H

#include "Material.h"

/**
 * Provides a porosity material property that may be constant
 * or provided by way of a coupled variable to simulate a heterogeneous
 * porosity.
 */
class NumbatPorosity : public Material
{
public:
  NumbatPorosity(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void computeQpProperties() override;

  /// Porosity (may be a coupled variable)
  const VariableValue & _input_porosity;
  /// Porosity material property
  MaterialProperty<Real> & _porosity;
  /// Optional random fluctuations in porosity
  const VariableValue & _random_noise;
};

#endif // NUMBATPOROSITY_H
