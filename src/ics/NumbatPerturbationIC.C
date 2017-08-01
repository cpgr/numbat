/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatPerturbationIC.h"
#include "MooseRandom.h"
#include "MooseMesh.h"
#include <cmath>

template <>
InputParameters
validParams<NumbatPerturbationIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addRangeCheckedParam<Real>(
      "amplitude",
      "amplitude >= 0 & amplitude <= 1",
      "The maximum amplitude of the random noise in the initial condition");
  params.addParam<unsigned int>("seed", 0, "Seed value for the random number generator");
  params.addClassDescription("Perturbed initial condition that can be used to initiate convection");
  return params;
}

NumbatPerturbationIC::NumbatPerturbationIC(const InputParameters & parameters)
  : InitialCondition(parameters), _amplitude(getParam<Real>("amplitude")), _mesh(_fe_problem.mesh())
{
  MooseRandom::seed(getParam<unsigned int>("seed"));

  unsigned int dim = _mesh.dimension();

  // The component is 1 for 2D meshses, 2 for 3D meshes. Note that
  // Numbat only works for 2D or 3D meshes
  if (dim == 1)
    mooseError("Numbat only works for 2D or 3D meshes");
  else
    _component = dim - 1;

  // The maximum extent of the mesh in the vertical (component) direction is
  _mesh_max = _mesh.getMaxInDimension(_component);
}

Real
NumbatPerturbationIC::value(const Point & p)
{
  // Random number between 0 and 1
  Real random_real = MooseRandom::rand();

  // The initial diffusive profile for t = 1;
  Real initial_diff = 1.0 + std::erf((p(_component) - _mesh_max) / 2.0);

  // Add a random perturbation taken from [- a * c1 * r / 2, a * c1 * r / 2]
  // where a is the amplitude specified in the input file,
  // c1 is the initial diffusive concentration profile at t = 1,
  // and r is a random number sampled from [0,1]
  Real initial_perturbation = _amplitude * initial_diff * (random_real - 0.5);

  // Bound the perturbed concentration so that it is [0,1]
  Real initial_concentration = initial_diff + initial_perturbation;

  if (initial_concentration < 0.0)
    initial_concentration = 0.0;
  else if (initial_concentration > 1.0)
    initial_concentration = 1.0;

  return initial_concentration;
}
