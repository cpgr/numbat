/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATSIDEFLUXSF_H
#define NUMBATSIDEFLUXSF_H

#include "SideIntegralVariablePostprocessor.h"

class NumbatSideFluxSF;

template <>
InputParameters validParams<NumbatSideFluxSF>();

/**
 * Calculates dimensionless flux over boundary for the streamfunction
 * formulation
 */
class NumbatSideFluxSF : public SideIntegralVariablePostprocessor
{
public:
  NumbatSideFluxSF(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral() override;
};

#endif // NUMBATSIDEFLUXSF_H
