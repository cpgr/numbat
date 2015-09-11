/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef PERTURBATIONIC_H
#define PERTURBATIONIC_H

// MOOSE Includes
#include "InitialCondition.h"

// Forward Declarations
class PerturbationIC;

template<>
InputParameters validParams<PerturbationIC>();

/**
 * PerturbationIC just returns a constant value.
 */
class PerturbationIC : public InitialCondition
{
public:

  /**
   * Constructor: Same as the rest of the MOOSE Objects
   */
  PerturbationIC(const InputParameters & parameters);

  /**
   * The value of the variable at a point.
   *
   * This must be overriden by derived classes.
   */
  virtual Real value(const Point & p);

private:
  Real _amplitude;
};

#endif //PERTURBATIONIC_H
