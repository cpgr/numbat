/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef THREEDCONVECTIONDIFFUSIONDDC_H
#define THREEDCONVECTIONDIFFUSIONDDC_H

#include "Kernel.h"

class ThreeDConvectionDiffusionDDC;

template<>
InputParameters validParams<ThreeDConvectionDiffusionDDC>();

class ThreeDConvectionDiffusionDDC : public Kernel
{
public:

  ThreeDConvectionDiffusionDDC(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

//  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  RealTensorValue _gamma;

private:

  VariableGradient & _grad_streamfunctiony;
  VariableGradient & _grad_streamfunctionx;
  unsigned int _grad_streamfunctionx_var;
  unsigned int _grad_streamfunctiony_var;
};

#endif //THREEDCONVECTIONDIFFUSIONDDC_H
