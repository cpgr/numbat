/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef TWODCONVECTIONDIFFUSIONDDC_H
#define TWODCONVECTIONDIFFUSIONDDC_H

#include "Kernel.h"

class TwoDConvectionDiffusionDDC;

template<>
InputParameters validParams<TwoDConvectionDiffusionDDC>();

class TwoDConvectionDiffusionDDC : public Kernel
{
public:

  TwoDConvectionDiffusionDDC(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int jvar);


private:

  RealTensorValue _gamma_tensor;
  VariableGradient & _grad_streamfunction;
  unsigned int _grad_streamfunction_var;
};

#endif //TWODCONVECTIONDIFFUSIONDDC_H
