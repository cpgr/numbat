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

#include "VerticalRefine.h"

#include "libmesh/mesh_modification.h"
#include "libmesh/mesh_base.h"

template<>
InputParameters validParams<VerticalRefine>()
{
  InputParameters params = validParams<MeshModifier>();
  params.addRequiredParam<Real>("mesh_top", "The coordinate of the top of the mesh");
  params.addRequiredParam<Real>("mesh_bottom", "The coordinate of the bottom of the mesh");

  return params;
}

VerticalRefine::VerticalRefine(const std::string & name, InputParameters parameters):
    MeshModifier(name, parameters),
    _mesh_top_value(getParam<Real>("mesh_top")),
    _mesh_bottom_value(getParam<Real>("mesh_bottom"))
{
}

VerticalRefine::~VerticalRefine()
{
}

void
VerticalRefine::modify()
{
   VerticalRefine::cosinescale(*_mesh_ptr, _mesh_top_value, _mesh_bottom_value);
}

void
VerticalRefine::cosinescale(libMesh::MeshBase & mesh, const Real mt, const Real mb)
{
   const Real pihalf = libMesh::pi / 2.0;
   const Real mrange = mt - mb;
   const libMesh::MeshBase::node_iterator nd_end = mesh.nodes_end();

   // Cosine scale of the y coordinate in two dimensions
   if (mesh.mesh_dimension() == 2)
     {
      for (libMesh::MeshBase::node_iterator nd = mesh.nodes_begin(); nd != nd_end; ++nd)
         {
           (**nd)(1) = mt - mrange * (1 - std::cos(pihalf * ((**nd)(1) - mt) / mrange));
         }
     }

   // Cosine scale of the z coordinate in two dimensions
   if (mesh.mesh_dimension() == 3)
     {
      for (libMesh::MeshBase::node_iterator nd = mesh.nodes_begin(); nd != nd_end; ++nd)
         {
           (**nd)(2) = mt - mrange * (1 - std::cos(pihalf * ((**nd)(2) - mt) / mrange));
         }
     }
}
