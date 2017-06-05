/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATSIDEFLUX_H
#define NUMBATSIDEFLUX_H

#include "SideIntegralVariablePostprocessor.h"

class NumbatSideFlux;

template <>
InputParameters validParams<NumbatSideFlux>();

/**
 * Calculates flux over boundary
 */
class NumbatSideFlux : public SideIntegralVariablePostprocessor
{
public:
  NumbatSideFlux(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral() override;

  /// Porosity
  const MaterialProperty<Real> & _porosity;
  /// Diffusivity
  const MaterialProperty<Real> & _diffusivity;
  /// Density
  const MaterialProperty<Real> & _density;
};

#endif // NUMBATSIDEFLUX_H
