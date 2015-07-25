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
