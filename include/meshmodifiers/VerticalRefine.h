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

#ifndef VERTICALREFINE_H
#define VERTICALREFINE_H

#include "MeshModifier.h"

class Transform;

template<>
InputParameters validParams<Transform>();

class VerticalRefine : public MeshModifier
{
public:
  VerticalRefine(const InputParameters & parameters);


  virtual ~VerticalRefine();

protected:
  void modify();
  void cosinescale(libMesh::MeshBase & mesh, const Real mt, const Real mb);

  Real _mesh_top_value;
  Real _mesh_bottom_value;
};

#endif /* VERTICALREFINE_H */
