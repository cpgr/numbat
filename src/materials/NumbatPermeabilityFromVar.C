/*****************************************************************/
/*      NUMBAT - NUMerical Boussinesq Advective Transport        */
/*                                                               */
/*           All contents are licensed under MIT/BSD             */
/*              See LICENSE for full restrictions                */
/*****************************************************************/

#include "NumbatPermeabilityFromVar.h"

registerMooseObject("NumbatApp", NumbatPermeabilityFromVar);

InputParameters
NumbatPermeabilityFromVar::validParams()
{
  InputParameters params = Material::validParams();
  params.addRequiredCoupledVar("perm_xx", "The xx component of the permeability tensor");
  params.addRequiredCoupledVar("perm_yy", "The yy component of the permeability tensor");
  params.addRequiredCoupledVar("perm_zz", "The zz component of the permeability tensor");
  params.addCoupledVar("perm_xy", 0.0, "The xy component of the permeability tensor");
  params.addCoupledVar("perm_xz", 0.0, "The xz component of the permeability tensor");
  params.addCoupledVar("perm_yx", 0.0, "The yx component of the permeability tensor");
  params.addCoupledVar("perm_yz", 0.0, "The yz component of the permeability tensor");
  params.addCoupledVar("perm_zx", 0.0, "The zx component of the permeability tensor");
  params.addCoupledVar("perm_zy", 0.0, "The zy component of the permeability tensor");
  params.addClassDescription(
      "This Material provides the permeability tensor given by the input variables");
  return params;
}

NumbatPermeabilityFromVar::NumbatPermeabilityFromVar(const InputParameters & parameters)
  : Material(parameters),
    _perm_xx(coupledValue("perm_xx")),
    _perm_xy(coupledValue("perm_xy")),
    _perm_xz(coupledValue("perm_xz")),
    _perm_yx(coupledValue("perm_yx")),
    _perm_yy(coupledValue("perm_yy")),
    _perm_yz(coupledValue("perm_yz")),
    _perm_zx(coupledValue("perm_zx")),
    _perm_zy(coupledValue("perm_zy")),
    _perm_zz(coupledValue("perm_zz")),
    _permeability(declareProperty<RealTensorValue>("permeability"))
{
}

void
NumbatPermeabilityFromVar::computeQpProperties()
{
  RealTensorValue permeability(_perm_xx[_qp],
                               _perm_xy[_qp],
                               _perm_xz[_qp],
                               _perm_yx[_qp],
                               _perm_yy[_qp],
                               _perm_yz[_qp],
                               _perm_zx[_qp],
                               _perm_zy[_qp],
                               _perm_zz[_qp]);

  _permeability[_qp] = permeability;
}
