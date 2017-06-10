/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATDARCYSF_H
#define NUMBATDARCYSF_H

#include "Kernel.h"
#include "MooseMesh.h"

class NumbatDarcySF;

template <>
InputParameters validParams<NumbatDarcySF>();

class NumbatDarcySF : public Kernel
{
public:
  NumbatDarcySF(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  /// Permeability anisotropy kv/kh
  Real _gamma;
  /// The gradient of the concentration variable
  const VariableGradient & _grad_concentration;
  /// The variable number of the concentration variable
  unsigned int _grad_concentration_var;
  /// The component of the streamfunction variable
  const MooseEnum & _component;
  /// The mesh dimension
  unsigned int _mesh_dimension;
};

#endif // NUMBATDARCYSF_H
