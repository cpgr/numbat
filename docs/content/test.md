<div class="page-wrap">

-   [Installation](../getting_started/index.html)

<!-- -->

-   [Governing equations](../governing_equations/index.html)

<!-- -->

-   [Available objects](../systems/index.html)

<!-- -->

-   [Input file syntax](index.html)
-   [2D](../example2D/index.html)
-   [3D](../example3D/index.html)

<!-- -->

-   [User manual](../download/index.html)

<div class="nav-wrapper container">

[Numbat](../index.html){.page-title}
-   [Getting Started*arrow\_drop\_down*](#!){.dropdown-button}
-   [Theory*arrow\_drop\_down*](#!){.dropdown-button}
-   [Systems*arrow\_drop\_down*](#!){.dropdown-button}
-   [Examples*arrow\_drop\_down*](#!){.dropdown-button}
-   [Manual*arrow\_drop\_down*](#!){.dropdown-button}
-   <div class="input-field search-wrapper">

    *search* *close*
    <div class="search-results">

    </div>

    </div>

-   [![](../media/github-mark-light.png){.github-mark}GitHub](https://github.com/cpgr/numbat){.github-mark-label}

</div>

<div class="container">

<div class="row">

<div class="col s12 m12 l12">

<div class="nav-wrapper">

<div class="col s12 m9 l10">

<span class="breadcrumb"></span> [](../index.html){.breadcrumb}
[input\_file\_syntax](index.html){.breadcrumb}

</div>

</div>

</div>

</div>

<div class="row">

<div id="moose-markdown-content" class="col s12 m8 l9">

Input file syntax
=================

The input file for a Numbat simulation is a simple, block-structured
text file based on the input files for a plain
[MOOSE](http://www.mooseframework.org) input file.

<div id="essential-input" class="section scrollspy">

Essential input
---------------

Details of the minimum input file requirements are given below.

### Mesh

All simulations must feature a mesh. For the basic model with a
rectangular mesh, the built-in MOOSE *GeneratedMesh* can be used to
create a suitable mesh. In 2D, the input block looks like:

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[Mesh]
  type = 'GeneratedMesh'
  dim = '2'
  ymax = '1.5'
  nx = '100'
  ny = '50'
[]
```

<div>

[(2Dddc.i)](https://github.com/cpgr/numbat/blob/master/examples/2D/isotropic/2Dddc.i){.moose-listing-link
.tooltipped}

</div>

</div>

In 3D, the Mesh block would look like:

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[Mesh]
  type = 'GeneratedMesh'
  dim = '3'
  zmax = '1.5'
  nx = '20'
  ny = '20'
  nz = '500'
[]
```

<div>

[(3Dddc.i)](https://github.com/cpgr/numbat/blob/master/examples/3D/isotropic/3Dddc.i){.moose-listing-link
.tooltipped}

</div>

</div>

### Variables

The number and type of variables required depends on the chosen
formulation. For the dimensional formulation, two nonlinear variables
must be provided, representing the fluid pressure and solute
concentration.

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[Variables]
  [./concentration]
    initial_condition = '0'
    scaling = '1e6'
  [../]
  [./pressure]
    initial_condition = '1e6'
  [../]
[]
```

<div>

[(2Dddc.i)](https://github.com/cpgr/numbat/blob/master/examples/2D/isotropic/2Dddc.i){.moose-listing-link
.tooltipped}

</div>

</div>

For the dimensionless streamfunction formulation, the nonlinear
variables for a 2D simulations are solute concentration and
streamfunction:

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[Variables]
  [./concentration]
    order = 'FIRST'
    family = 'LAGRANGE'
    [./InitialCondition]
      type = 'NumbatPerturbationIC'
      variable = 'concentration'
      amplitude = '0.1'
      seed = '1'
    [../]
  [../]
  [./streamfunction]
    order = 'FIRST'
    family = 'LAGRANGE'
    initial_condition = '0.0'
  [../]
[]
```

<div>

[(2DddcSF.i)](https://github.com/cpgr/numbat/blob/master/examples/2D/isotropic/2DddcSF.i){.moose-listing-link
.tooltipped}

</div>

</div>

In 3D, an additional streamfunction variable must also be added:

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[Variables]
  [./concentration]
    order = 'FIRST'
    family = 'LAGRANGE'
    [./InitialCondition]
      type = 'NumbatPerturbationIC'
      variable = 'concentration'
      amplitude = '0.1'
      seed = '1'
    [../]
  [../]
  [./streamfunctionx]
    order = 'FIRST'
    family = 'LAGRANGE'
    initial_condition = '0.0'
  [../]
  [./streamfunctiony]
    order = 'FIRST'
    family = 'LAGRANGE'
    initial_condition = '0.0'
  [../]
[]
```

<div>

[(3DddcSF.i)](https://github.com/cpgr/numbat/blob/master/examples/3D/isotropic/3DddcSF.i){.moose-listing-link
.tooltipped}

</div>

</div>

### Materials

For the dimensional formulation, several material and fluid properties
are required: porosity, permeability, fluid density and viscosity, and
diffusivity. These can be added using the following Numbat materials:

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[Materials]
  [./porosity]
    type = 'NumbatPorosity'
    porosity = '0.3'
    noise = 'noise'
  [../]
  [./permeability]
    type = 'NumbatPermeability'
    permeability = '1e-11 0 0 0 1e-11 0 0 0 1e-11'
  [../]
  [./diffusivity]
    type = 'NumbatDiffusivity'
    diffusivity = '2e-9'
  [../]
  [./density]
    type = 'NumbatDensity'
    concentration = 'concentration'
    zero_density = '995'
    delta_density = '10.5'
    saturated_concentration = '0.049306'
  [../]
  [./viscosity]
    type = 'NumbatViscosity'
    viscosity = '6e-4'
  [../]
[]
```

<div>

[(2Dddc.i)](https://github.com/cpgr/numbat/blob/master/examples/2D/isotropic/2Dddc.i){.moose-listing-link
.tooltipped}

</div>

</div>

<div class="admonition note">

Note

No material properties are required in the dimensionless streamfunction
formulation

</div>

### Kernels

Three kernels are required for a 2D model: a *NumbatDarcySF* kernel for
the *streamfunction* variable, a *NumbatConvectionDiffusionSF* kernel
for the *concentration* variable, and a *TimeDerivative* kernel also for
the *concentration* variable. An example for an isotropic model is

    [Kernels]
      [./Darcy]
        type = NumbatDarcySF
        variable = streamfunction
        concentration_variable = concentration
      [../]
      [./ConvectionDiffusion]
        type = NumbatConvectionDiffusionSF
        variable = concentration
        streamfunction_variable = streamfunction
        coeff_tensor = '1 0 0 0 1 0 0 0 1'
      [../]
      [./TimeDerivative]
        type = TimeDerivative
        variable = concentration
      [../]
    []

The *coeff\_tensor* parameter in each convective diffusion kernel can be
modified. The format of this

For 3D models, an additional *NumbatDarcySF* kernel is required for the
additional stream function variable. An example of the kernels block for
a 3D isotropic model is

    [Kernels]
      [./Darcy]
        type = NumbatDarcySF
        variable = streamfunctionx
        concentration_variable = concentration
        component = x
      [../]
      [./Darcy]
        type = NumbatDarcySF
        variable = streamfunctiony
        concentration_variable = concentration
        component = y
      [../]
      [./ConvectionDiffusion]
        type = NumbatConvectionDiffusionSF
        variable = concentration
        streamfunction_variable = 'streamfunctionx streamfunctiony'
        coeff_tensor = '1 0 0 0 1 0 0 0 1'
      [../]
      [./TimeDerivative]
        type = TimeDerivative
        variable = concentration
      [../]
    []

In the 3D case, it is important to note that the *NumbatDarcySF* kernel
must specify the component that it applies to, and that the
*streamfunction\_variable* keyword in the *NumbatConvectionDiffusionSF*
kernel must contain both *streamfunction* variables ordered by the *x*
component then the *y* component.

### Initial condition

To seed the instability, a random perturbation to the initial
concentration is prescribed using the *NumbatPerturbationIC* initial
condition. This can be applied in the *Variables* block in the input
file (see above) using

    [./InitialCondition]
      type = NumbatPerturbationIC
      variable = concentration
      amplitude = 0.01
      seed = 1
    [../]

The *NumbatPerturbationIC* initial condition applies the diffusive
concentration profile to the nodes for (scaled) time
,
for
, where
is the error function.
A uniform random perturbation is then added to the diffusive
concentration profile, where the amplitude of the perturbation is
specified by the input file value *amplitude*.

### Boundary conditions

Appropriate boundary conditions must be prescribed. Typically, these
will be constant concentration at the top of the model domain, periodic
boundary conditions on the lateral sides (to mimic an infinite model),
and no-flow boundary conditions at the top and bottom surfaces.

In the 2D dimensional formulation, this can be achieved using the
following input block:

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[BCs]
  [./conctop]
    type = 'PresetBC'
    variable = 'concentration'
    boundary = 'top'
    value = '0.049306'
  [../]
  [./Periodic]
    [./x]
      variable = 'concentration'
      auto_direction = 'x'
    [../]
  [../]
[]
```

<div>

[(2Dddc.i)](https://github.com/cpgr/numbat/blob/master/examples/2D/isotropic/2Dddc.i){.moose-listing-link
.tooltipped}

</div>

</div>

while in 3D

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[BCs]
  [./conctop]
    type = 'PresetBC'
    variable = 'concentration'
    boundary = 'front'
    value = '0.049306'
  [../]
  [./Periodic]
    [./x]
      variable = 'concentration'
      auto_direction = 'x y'
    [../]
  [../]
[]
```

<div>

[(3Dddc.i)](https://github.com/cpgr/numbat/blob/master/examples/3D/isotropic/3Dddc.i){.moose-listing-link
.tooltipped}

</div>

</div>

In this case, the *conctop* boundary condition is a Dirichlet condition
at the top of the model that fixes the value of concentration.

It is useful to note that a MOOSE *GeneratedMesh* provides descriptive
names for the sides of the model (top, bottom, left, right) which can be
referenced in the input file.

For the dimensionless streamfunction formulation, no-flow boundary
conditions are prescribed on the top and bottom surfaces by holding the
*streamfunction* variable constant (in this case 0).

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[BCs]
  [./conctop]
    type = 'DirichletBC'
    variable = 'concentration'
    boundary = 'top'
    value = '1.0'
  [../]
  [./streamfuntop]
    type = 'DirichletBC'
    variable = 'streamfunction'
    boundary = 'top'
    value = '0.0'
  [../]
  [./streamfunbottom]
    type = 'DirichletBC'
    variable = 'streamfunction'
    boundary = 'bottom'
    value = '0.0'
  [../]
  [./Periodic]
    [./x]
      variable = 'concentration streamfunction'
      auto_direction = 'x'
    [../]
  [../]
[]
```

<div>

[(2DddcSF.i)](https://github.com/cpgr/numbat/blob/master/examples/2D/isotropic/2DddcSF.i){.moose-listing-link
.tooltipped}

</div>

</div>

### Executioner

Each MOOSE simulation must use an *Executioner*, which provides
parameters for the solve.

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[Executioner]
  type = 'Transient'
  l_max_its = '200'
  end_time = '3e5'
  solve_type = 'NEWTON'
  petsc_options = '-ksp_snes_ew'
  petsc_options_iname = '-pc_type -sub_pc_type -ksp_atol'
  petsc_options_value = 'bjacobi ilu 1e-12'
  nl_abs_tol = '1e-10'
  nl_max_its = '25'
  dtmax = '2e3'
  [./TimeStepper]
    type = 'IterationAdaptiveDT'
    dt = '1'
  [../]
[]
```

<div>

[(2Dddc.i)](https://github.com/cpgr/numbat/blob/master/examples/2D/isotropic/2Dddc.i){.moose-listing-link
.tooltipped}

</div>

</div>

Executioners are a standard MOOSE feature that are well documented on
the [MOOSE](http://www.mooseframework.org), so no further detail is
provided here.

### Preconditioning

A default preconditioning block is used that provides all Jacobian
entries to aid convergence.

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[Preconditioning]
  [./smp]
    type = 'SMP'
    full = 'true'
  [../]
[]
```

<div>

[(2Dddc.i)](https://github.com/cpgr/numbat/blob/master/examples/2D/isotropic/2Dddc.i){.moose-listing-link
.tooltipped}

</div>

</div>

This is a standard MOOSE feature that is documented on the
[MOOSE](http://www.mooseframework.org) website, so no further detail is
provided here.

### Outputs

To provide ouptut from the simulation, an *Outputs* block must be
specified. An example is

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[Outputs]
  [./console]
    type = 'Console'
    perf_log = 'true'
    output_nonlinear = 'true'
  [../]
  [./exodus]
    type = 'Exodus'
    file_base = '2Dddc'
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  [./csvoutput]
    type = 'CSV'
    file_base = '2Dddc'
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
```

<div>

[(2Dddc.i)](https://github.com/cpgr/numbat/blob/master/examples/2D/isotropic/2Dddc.i){.moose-listing-link
.tooltipped}

</div>

</div>

There are a large number of output options available in MOOSE, see the
[MOOSE](http://www.mooseframework.org) website for further details.

</div>

<div id="optional-input" class="section scrollspy">

Optional input
--------------

While the above required blocks will enable a Numbat simulation to run,
there are a number of optional input blocks that will improve the
simulations are increase the amount of rsults provided.

### Mesh modifier

This creates a 2D mesh from
to
and
to
with 80 elements in the
-direction and 20 elements in the
-direction. It is useful to have a mesh that is more refined at the top
of the model, to accurately capture the initially small structure of the
convective fingers. This is achieved using the built-in *bias\_y*
parameter.
### Mesh adaptivity

MOOSE features built-in mesh adaptivity that is extremely useful in
Numbat simulations to reduce computational expense. This can be included
using:

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[Adaptivity]
  max_h_level = '1'
  initial_marker = 'boxmarker'
  initial_steps = '1'
  marker = 'errormarker'
  [./Indicators]
    [./gradjumpindicator]
      type = 'GradientJumpIndicator'
      variable = 'concentration'
    [../]
  [../]
  [./Markers]
    [./errormarker]
      type = 'ErrorToleranceMarker'
      refine = '0.05'
      indicator = 'gradjumpindicator'
    [../]
    [./boxmarker]
      type = 'BoxMarker'
      bottom_left = '0 0 -10'
      top_right = '500 500 0'
      inside = 'refine'
      outside = 'dont_mark'
    [../]
  [../]
[]
```

<div>

[(3DddcSF.i)](https://github.com/cpgr/numbat/blob/master/examples/3D/isotropic/3DddcSF.i){.moose-listing-link
.tooltipped}

</div>

</div>

For details about mesh adaptivity, see the
[MOOSE](http://www.mooseframework.org) website.

### Postprocessors

The flux over the top boundary or the total mass of solute in the model
is of particular interest in many cases (especially convective mixing of
CO
). These can be calculated at each time step using the
[NumbatSideFlux](../documentation/systems/Postprocessors/numbat/NumbatSideFlux/index.html)
and
[NumbatTotalMass](../documentation/systems/Postprocessors/numbat/NumbatTotalMass/index.html)
Postprocessors.

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[Postprocessors]
  [./boundaryfluxint]
    type = 'NumbatSideFlux'
    variable = 'concentration'
    boundary = 'top'
  [../]
  [./mass]
    type = 'NumbatTotalMass'
    variable = 'concentration'
  [../]
[]
```

<div>

[(2Dddc.i)](https://github.com/cpgr/numbat/blob/master/examples/2D/isotropic/2Dddc.i){.moose-listing-link
.tooltipped}

</div>

</div>

Versions of these Postprocessors for the dimensionless streamfunction
formulation are also provided, see
[NumbatSideFluxSF](../documentation/systems/Postprocessors/numbat/NumbatSideFluxSF/index.html)
and
[NumbatTotalMassSF](../documentation/systems/Postprocessors/numbat/NumbatTotalMassSF/index.html)
for details.

Numbat also provides a simple Postprocessor to calculate the Rayleigh
number for dimensional simulations, see
[NumbatRayleighNumber](../documentation/systems/Postprocessors/numbat/NumbatRayleighNumber/index.html)
for details.

### Velocity components

The velocity components in the
and
directions (in 2D), and
,
, and
directions in 3D can be calculated using the auxiliary system. These
velocity components are calculated using the streamfunction(s), see the
governing equations for details.
In the 2D case, two auxiliary variables,
and
, can be defined for the horizontal and vertical velocity components,
respectively.
<div class="admonition note">

Note

Importantly, these auxiliary variables **must** have monomial shape
functions (these are referred to as *elemental* variables, as the value
is constant over each mesh element). This restriction is due to fact
that the gradient of variables is undefined for *nodal* auxiliary
variables (for example, those using linear Lagrange shape functions).

</div>

An example of the input syntax for the 2D case is

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[AuxVariables]
  [./u]
    order = 'CONSTANT'
    family = 'MONOMIAL'
  [../]
  [./w]
    order = 'CONSTANT'
    family = 'MONOMIAL'
  [../]
[]
```

<div>

[(2DddcSF.i)](https://github.com/cpgr/numbat/blob/master/examples/2D/isotropic/2DddcSF.i){.moose-listing-link
.tooltipped}

</div>

</div>

For the 3D case, there is an additional horizontal velocity component
(*v*), so the input syntax is

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[AuxVariables]
  [./u]
    order = 'CONSTANT'
    family = 'MONOMIAL'
  [../]
  [./v]
    order = 'CONSTANT'
    family = 'MONOMIAL'
  [../]
  [./w]
    order = 'CONSTANT'
    family = 'MONOMIAL'
  [../]
[]
```

<div>

[(3DddcSF.i)](https://github.com/cpgr/numbat/blob/master/examples/3D/isotropic/3DddcSF.i){.moose-listing-link
.tooltipped}

</div>

</div>

The velocity components are calculated by
[NumbatDarcyVelocity](../documentation/systems/AuxKernels/numbat/NumbatDarcyVelocity/index.html)
AuxKernels (or
[NumbatDarcyVelocitySF](../documentation/systems/AuxKernels/numbat/NumbatDarcyVelocitySF/index.html)
AuxKernels for the dimensionless streamfunction formulation). Each
velocity component is computed by an AuxKernel.

For the 2D case, two AuxKernels are required:

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[AuxKernels]
  [./uAux]
    type = 'NumbatDarcyVelocitySF'
    variable = 'u'
    component = 'x'
    streamfunction_variable = 'streamfunction'
  [../]
  [./wAux]
    type = 'NumbatDarcyVelocitySF'
    variable = 'w'
    component = 'y'
    streamfunction_variable = 'streamfunction'
  [../]
[]
```

<div>

[(2DddcSF.i)](https://github.com/cpgr/numbat/blob/master/examples/2D/isotropic/2DddcSF.i){.moose-listing-link
.tooltipped}

</div>

</div>

while for 3D, three AuxKernels are necessary:

<div class="moose-float-div moose-listing-div" style="label:False;">

``` {style="overflow-y:scroll;max-height:350px"}
copy[AuxKernels]
  [./uAux]
    type = 'NumbatDarcyVelocitySF'
    variable = 'u'
    component = 'x'
    streamfunction_variable = 'streamfunctionx streamfunctiony'
  [../]
  [./vAux]
    type = 'NumbatDarcyVelocitySF'
    variable = 'v'
    component = 'y'
    streamfunction_variable = 'streamfunctionx streamfunctiony'
  [../]
  [./wAux]
    type = 'NumbatDarcyVelocitySF'
    variable = 'w'
    component = 'z'
    streamfunction_variable = 'streamfunctionx streamfunctiony'
  [../]
[]
```

<div>

[(3DddcSF.i)](https://github.com/cpgr/numbat/blob/master/examples/3D/isotropic/3DddcSF.i){.moose-listing-link
.tooltipped}

</div>

</div>

<div class="admonition note">

Note

For the 3D case, both streamfunction variables must be given, in the
correct order (eg.
then
)

</div>

</div>

</div>

<div class="col hid-on-small-only m4 l3">

<div class="toc-wrapper pin-top">

<div class="moose-devel-links-container">

</div>

<div class="section table-of-contents">

-   [Essential input](#essential-input)
-   [Optional input](#optional-input)

</div>

</div>

</div>

</div>

</div>

</div>

<div class="container white-text">

<div class="row">

<div class="col s12">

Site Generated with [MOOSE](https://www.mooseframework.org)

[Edit
Markdown](https://github.com/cpgr/numbat/edit/devel/docs/content/input_file_syntax.md){.moose-edit-markdown}

</div>

</div>

</div>
