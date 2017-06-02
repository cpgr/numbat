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
  /// Fluctuations in value
  const VariableValue & _random_noise;
  /// Nodes that this boundary condition acts on that are also present in other
  /// boundaries - these must not have fluctuations added to ensure periodic
  // boundary conditions can be applied
  std::set<dof_id_type> _shared_boundary_nodes;
};

#endif // NUMBATPERTURBATIONBC_H
