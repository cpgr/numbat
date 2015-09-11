/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef CONVECTIONDIFFUSIONDDC_H
#define CONVECTIONDIFFUSIONDDC_H

#include "Kernel.h"

class ConvectionDiffusionDDC;

template<>
InputParameters validParams<ConvectionDiffusionDDC>();

class ConvectionDiffusionDDC : public Kernel
{
public:

  ConvectionDiffusionDDC(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:

  /// Diffusion tensor
  RealTensorValue _gamma;
  /// Gradient of the streamfunction variable(s)
  std::vector<VariableGradient *> _grad_streamfunction;
  /// MOOSE variable number of the coupled streamfunction variable(s)
  std::vector<unsigned int> _streamfunction_var;
  /// The mesh dimension
  unsigned int _mesh_dimension;
};

#endif //CONVECTIONDIFFUSIONDDC_H
