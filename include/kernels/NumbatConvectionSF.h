/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATCONVECTIONSF_H
#define NUMBATCONVECTIONSF_H

#include "Kernel.h"
#include "MooseMesh.h"

class NumbatConvectionSF : public Kernel
{
public:
  NumbatConvectionSF(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  /// Gradient of the streamfunction variable(s)
  std::vector<const VariableGradient *> _grad_streamfunction;
  /// MOOSE variable number of the coupled streamfunction variable(s)
  std::vector<unsigned int> _streamfunction_var;
  /// The mesh dimension
  unsigned int _mesh_dimension;
};

#endif // NUMBATCONVECTIONSF_H
