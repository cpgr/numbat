/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatViscosity.h"

registerMooseObject("NumbatApp", NumbatViscosity);

InputParameters
NumbatViscosity::validParams()
{
  InputParameters params = Material::validParams();
  params.addRequiredParam<Real>("viscosity", "The viscosity");
  params.addClassDescription("This Material provides a viscosity material property");
  return params;
}

NumbatViscosity::NumbatViscosity(const InputParameters & parameters)
  : Material(parameters),
    _input_viscosity(getParam<Real>("viscosity")),
    _viscosity(declareProperty<Real>("viscosity"))
{
}

void
NumbatViscosity::computeQpProperties()
{
  _viscosity[_qp] = _input_viscosity;
}
