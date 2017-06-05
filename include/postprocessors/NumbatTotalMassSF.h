/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NUMBATTOTALMASSSF_H
#define NUMBATTOTALMASSSF_H

#include "ElementIntegralVariablePostprocessor.h"

class NumbatTotalMassSF;

template <>
InputParameters validParams<NumbatTotalMassSF>();

/**
 * Calculates total dimensionless mass in domain
 */
class NumbatTotalMassSF : public ElementIntegralVariablePostprocessor
{
public:
  NumbatTotalMassSF(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral() override;
};

#endif // NUMBATTOTALMASSSF_H
