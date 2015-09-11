/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
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
