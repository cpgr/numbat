/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "PerturbationIC.h"
#include "MooseRandom.h"
#include "MooseMesh.h"
#include "math.h"

template<>
InputParameters validParams<PerturbationIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addRequiredParam<Real>("amplitude", "The maximum amplitude of the initial condition");
  params.addParam<unsigned int>("seed", 0, "Seed value for the random number generator");
  return params;
}

PerturbationIC::PerturbationIC(const InputParameters & parameters) :
    InitialCondition(parameters),
    _amplitude(getParam<Real>("amplitude")),
    _mesh(_fe_problem.mesh())
{
    MooseRandom::seed(getParam<unsigned int>("seed"));
}

Real
PerturbationIC::value(const Point & p)
{
  unsigned int dim = _mesh.dimension();
  Real random_real = MooseRandom::rand();
  unsigned int component;

  if (dim == 2)
    component = 1; /// y component
  else if (dim == 3)
    component = 2; /// z component
  else
    mooseError("Numbat only works for 2D or 3D meshes");

  Real initial_diff = 1.0 + erf(p(component) / 2.0);
  Real initial_perturbation = random_real * (_amplitude * std::sqrt(0.002) * std::abs(p(component)) * std::exp(0.5 - 0.001 * p(component) * p(component)));

  return initial_diff + initial_perturbation;
}
