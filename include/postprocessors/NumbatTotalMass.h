/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATTOTALMASS_H
#define NUMBATTOTALMASS_H

#include "ElementIntegralVariablePostprocessor.h"

class NumbatTotalMass;

template <>
InputParameters validParams<NumbatTotalMass>();

/**
 * Calculates total mass in domain
 */
class NumbatTotalMass : public ElementIntegralVariablePostprocessor
{
public:
  NumbatTotalMass(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral() override;

  /// Porosity
  const MaterialProperty<Real> & _porosity;
  /// Density
  const MaterialProperty<Real> & _density;
};

#endif // NUMBATTOTALMASS_H
