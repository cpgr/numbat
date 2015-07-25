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

#include "PerturbationIC.h"
#include "MooseRandom.h"
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
    _amplitude(getParam<Real>("amplitude"))
{
    MooseRandom::seed(getParam<unsigned int>("seed"));
}

Real
PerturbationIC::value(const Point & p)
{
  /**
   * _value * x
   * The Point class is defined in libMesh.  The spatial
   * coordinates x,y,z can be accessed individually using
   * the parenthesis operator and a numeric index from 0..2


   * In this case, p(1) is the y coordinate used for the 2D
   * case.
   */
  Real random_real = MooseRandom::rand();
  Real initial_diff = 1.0 + erf(p(1) / 2.0);
  Real initial_perturbation = random_real * (_amplitude * std::sqrt(0.002) * std::abs(p(1)) * std::exp(0.5 - 0.001 * p(1) * p(1)));

  return initial_diff + initial_perturbation;
}
