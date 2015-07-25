/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
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
