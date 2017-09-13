/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatBiasedMesh.h"

#include "libmesh/mesh_modification.h"
#include "libmesh/mesh_base.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<NumbatBiasedMesh>()
{
  InputParameters params = validParams<MeshModifier>();
  MooseEnum biased_enum("left right top bottom front back");
  params.addRequiredParam<MooseEnum>(
      "refined_edge", biased_enum, "The edge where the refinement should occur");
  params.addRequiredParam<Real>("refined_resolution",
                                "The resolution of the first element at the refined edge");
  params.addRequiredParam<unsigned int>("num_elems", "Number of elements along refined axis");
  params.addClassDescription("MeshModifier to bias the mesh with a specified initial resolution");
  return params;
}

NumbatBiasedMesh::NumbatBiasedMesh(const InputParameters & parameters)
  : MeshModifier(parameters),
    _initial_resolution(getParam<Real>("refined_resolution")),
    _biased_enum(getParam<MooseEnum>("refined_edge").getEnum<NumbatBiasedEnum>()),
    _num_elems(getParam<unsigned int>("num_elems"))
{
}

NumbatBiasedMesh::~NumbatBiasedMesh() {}

void
NumbatBiasedMesh::modify()
{
  // This modifier should only be applied to a regular orthogonal mesh
  const bool regular_orthogonal = _mesh_ptr->isRegularOrthogonal();
  if (!regular_orthogonal)
    mooseError("NumbatBiasedMesh can only be used on a regular orthogonal mesh");

  // Determine the axis that the refinement is to be applied
  unsigned int comp;
  bool refined_at_min = true;

  if (_biased_enum == NumbatBiasedEnum::LEFT)
    comp = 0;
  else if (_biased_enum == NumbatBiasedEnum::RIGHT)
  {
    comp = 0;
    refined_at_min = false;
  }
  else if (_biased_enum == NumbatBiasedEnum::TOP)
  {
    comp = 1;
    refined_at_min = false;
  }
  else if (_biased_enum == NumbatBiasedEnum::BOTTOM)
    comp = 1;
  else if (_biased_enum == NumbatBiasedEnum::FRONT)
  {
    comp = 2;
    refined_at_min = false;
  }
  else // _biased_enum == NumbatBiasedEnum::BACK
    comp = 2;

  // Calculate the scaling factor delta = 2 (width - n * _initial_resolution) / (n(n-1))
  const Real min = _mesh_ptr->getMinInDimension(comp);
  const Real max = _mesh_ptr->getMaxInDimension(comp);
  const Real width = max - min;

  const Real delta =
      2.0 * (width - _num_elems * _initial_resolution) / _num_elems / (_num_elems - 1);

  // Loop over the nodes and move them to the desired location
  libMesh::MeshBase::node_iterator node_it = _mesh_ptr->getMesh().nodes_begin();
  const libMesh::MeshBase::node_iterator node_end = _mesh_ptr->getMesh().nodes_end();

  std::vector<Real> node_coord;
  for (; node_it != node_end; ++node_it)
  {
    Node & node = **node_it;

    // The scaled index of the node. It will be close to a whole integer, or close
    // to a whole integer + 0.5 for the midnode in a quadratic element.
    // Note: start the indexing from min = 0 when refining at the smaller coord
    // values, or from max = 0 when refining at the larger end
    Real float_index;

    if (refined_at_min)
      float_index = (node(comp) - min) * _num_elems / width;
    else
      float_index = (max - node(comp)) * _num_elems / width;

    // Round float_index to an integer, so that 3.99 becomes 4 rather
    // than 3, etc
    unsigned int index = std::round(float_index);

    // Determine whether the node at the edge of an element (where the fractional_part
    // will be close to 0 or 1), or at the midpoint of an element (for a quadratic
    // element, where fractional_part will be close to 0.5)
    Real integer_part = 0.0;
    Real fractional_part = std::modf(float_index, &integer_part);

    if (std::abs(fractional_part) < TOLERANCE || std::abs(fractional_part - 1.0) < TOLERANCE)
    {
      // Leave the nodes along the boundaries alone
      if (index > 0 && index < _num_elems)
      {
        // Move the vertex nodes to the biased locations
        if (refined_at_min)
          node(comp) = min + index * _initial_resolution + 0.5 * index * (index - 1) * delta;
        else
          node(comp) = max - index * _initial_resolution - 0.5 * index * (index - 1) * delta;
      }
    }
    else if (std::abs(fractional_part - 0.5) < TOLERANCE)
    {
      // The nodes at the midpoint are not biased, rather they are moved so that
      // they are midway between the adjacent vertex nodes. Note that in this case,
      // integer_part will correspond to the index of the vertex on the left/bottom,
      // while integer_part + 1 will correspond to the index of the vertex on the
      // right/top
      Real lower, upper;
      if (refined_at_min)
      {
        lower = min + integer_part * _initial_resolution +
                0.5 * integer_part * (integer_part - 1) * delta;
        upper = min + (integer_part + 1) * _initial_resolution +
                0.5 * integer_part * (integer_part + 1) * delta;
      }
      else
      {
        upper = max - integer_part * _initial_resolution -
                0.5 * integer_part * (integer_part - 1) * delta;
        lower = max - (integer_part + 1) * _initial_resolution -
                0.5 * integer_part * (integer_part + 1) * delta;
      }

      node(comp) = lower + 0.5 * (upper - lower);
    }
    else
      mooseError("NumbatBiasedMesh does not work for element orders higher than 2. If linear or "
                 "quadratic elements have been used, then num_elems is probably incorrect. It "
                 "should be equal to the number of elements in the refined direction");

    node_coord.push_back(node(comp));
  }
}
