/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef DDCDENSITYAUX_H
#define DDCDENSITYAUX_H

#include "AuxKernel.h"

class DDCDensityAux;

template<>
InputParameters validParams<DDCDensityAux>();

class DDCDensityAux : public AuxKernel
{
public:

  DDCDensityAux(const InputParameters & parameters);

protected:

  virtual Real computeValue();

private:
  /// Water density
  Real _water_density;
  /// Solute density
  Real _solute_density;

  /// Solute mass fraction variable
  VariableValue & _solute_mass_fraction;
};

#endif //DDCDENSITYAUX_H
