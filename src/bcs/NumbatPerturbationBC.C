/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatPerturbationBC.h"
#include "MooseMesh.h"
#include "MooseVariable.h"

registerMooseObject("NumbatApp", NumbatPerturbationBC);

InputParameters
NumbatPerturbationBC::validParams()
{
  InputParameters params = DirichletBC::validParams();
  params.addRequiredParam<Real>("value", "Average value of the boundary condition");
  params.addCoupledVar("noise", 0, "Random noise");
  params.addClassDescription("Dirichlet boundary condition that includes a random perturbation");
  params.suppressParameter<bool>("preset"); // force preset (default = true)
  return params;
}

NumbatPerturbationBC::NumbatPerturbationBC(const InputParameters & parameters)
  : DirichletBC(parameters), _value(getParam<Real>("value")), _random_noise(coupledValue("noise"))
{
  // Get the boundary id(s) that this BC is acting on. Note that _current_boundary_id
  // is not set at this stage, so need to call boundaryIDs()
  const std::set<BoundaryID> & boundary_id = boundaryIDs();

  // Containers of nodes in the boundary(s) that this BC acts on and all other boundary nodes
  std::set<dof_id_type> perturbationbc_nodes;
  std::set<dof_id_type> other_boundary_nodes;

  // Get all nodes in all boundaries, and
  ConstBndNodeRange & bnd_nodes = *_mesh.getBoundaryNodeRange();
  for (auto & bnode : bnd_nodes)
  {
    // If the nodes are in the boundary(s) that this BC acts on, store them in one
    // container, otherwise store all others in other_boundary_nodes
    if (*boundary_id.find(bnode->_bnd_id) != *boundary_id.end())
      perturbationbc_nodes.insert(bnode->_node->id());
    else
      other_boundary_nodes.insert(bnode->_node->id());
  }

  // Now find all nodes in the boundary(s) that this BC applies to that are also
  // present in other_boundary_nodes - these nodes are on the edge and must have
  // no fluctuation added to them so that periodic boundary conditions can be used
  for (auto nid : perturbationbc_nodes)
    if (other_boundary_nodes.find(nid) != other_boundary_nodes.end())
      _shared_boundary_nodes.insert(nid);
}

Real
NumbatPerturbationBC::computeQpValue()
{
  Real fluctuation;
  if (_shared_boundary_nodes.find(_current_node->id()) != _shared_boundary_nodes.end())
    fluctuation = 0.0;
  else
    fluctuation = _random_noise[_qp];

  return _value - fluctuation;
}
