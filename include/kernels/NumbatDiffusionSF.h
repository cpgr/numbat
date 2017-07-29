/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATDIFFUSIONSF_H
#define NUMBATDIFFUSIONSF_H

#include "Kernel.h"
#include "MooseMesh.h"

class NumbatDiffusionSF;

template <>
InputParameters validParams<NumbatDiffusionSF>();

class NumbatDiffusionSF : public Kernel
{
public:
  NumbatDiffusionSF(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  /// Diffusion tensor
  RealTensorValue _gamma_tensor;
};

#endif // NUMBATDIFFUSIONSF_H
