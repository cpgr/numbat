/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#ifndef NUMBATDARCYVELOCITYSF_H
#define NUMBATDARCYVELOCITYSF_H

#include "AuxKernel.h"
#include "MooseMesh.h"

class NumbatDarcyVelocitySF : public AuxKernel
{
public:
  NumbatDarcyVelocitySF(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue();

private:
  /// The gradient of the streamfunction variable(s)
  std::vector<const VariableGradient *> _grad_streamfunction;
  /// The component of the velocity
  const MooseEnum & _component;
  /// The mesh dimension
  unsigned int _mesh_dimension;
};

#endif // NUMBATDARCYVELOCITYSF_H
