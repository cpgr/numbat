/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATCONVECTIONDIFFUSIONSF_H
#define NUMBATCONVECTIONDIFFUSIONSF_H

#include "Kernel.h"
#include "MooseMesh.h"

class NumbatConvectionDiffusionSF;

template <>
InputParameters validParams<NumbatConvectionDiffusionSF>();

class NumbatConvectionDiffusionSF : public Kernel
{
public:
  NumbatConvectionDiffusionSF(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  /// Diffusion tensor
  RealTensorValue _gamma_tensor;
  /// Gradient of the streamfunction variable(s)
  std::vector<const VariableGradient *> _grad_streamfunction;
  /// MOOSE variable number of the coupled streamfunction variable(s)
  std::vector<unsigned int> _streamfunction_var;
  /// The mesh dimension
  unsigned int _mesh_dimension;
};

#endif // NUMBATCONVECTIONDIFFUSIONSF_H
