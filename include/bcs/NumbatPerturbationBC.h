/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATPERTURBATIONBC_H
#define NUMBATPERTURBATIONBC_H

#include "PresetBC.h"

class NumbatPerturbationBC;

template <>
InputParameters validParams<NumbatPerturbationBC>();

/**
 * Dirichlet boundary condition for concentration with a random perturbation
 * along the boundary. Useful to initiate convective instability in Numbat
 * simulations
 */
class NumbatPerturbationBC : public PresetBC
{
public:
  NumbatPerturbationBC(const InputParameters & parameters);

protected:
  virtual Real computeQpValue() override;
  /// Average value for this BC
  const Real & _value;
  /// Amplitude of the random perturbation
  const Real _amplitude;
};

#endif // NUMBATPERTURBATIONBC_H
