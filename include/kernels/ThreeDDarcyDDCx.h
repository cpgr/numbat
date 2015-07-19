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

#ifndef THREEDDARCYDDCX_H
#define THREEDDARCYDDCX_H

#include "Kernel.h"

class ThreeDDarcyDDCx;

template<>
InputParameters validParams<ThreeDDarcyDDCx>();

class ThreeDDarcyDDCx : public Kernel
{
public:

  ThreeDDarcyDDCx(const std::string & name,
             InputParameters parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:

  Real _gamma;
  VariableGradient & _grad_concentration;
  unsigned int _grad_concentration_var;
};

#endif //THREEDDARCYDDCX_H
