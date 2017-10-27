# Input file syntax

The input file for a Numbat simulation is a simple, block-structured
text file based on the input files for a plain [MOOSE] input file.

## Essential input

Details of the minimum input file requirements are given below.

### Mesh

All simulations must feature a mesh. For the basic model with a
rectangular mesh, the built-in MOOSE `GeneratedMesh` can be used to
create a suitable mesh. In 2D, the input block looks like:

!listing examples/2D/isotropic/2Dddc.i block=Mesh label=False

In 3D, the Mesh block would look like:

!listing examples/3D/isotropic/3Dddc.i block=Mesh label=False

### Variables

The number and type of variables required depends on the chosen formulation. For the
dimensional formulation, two nonlinear variables must be provided, representing the fluid pressure and solute concentration.

!listing examples/2D/isotropic/2Dddc.i block=Variables label=False

For the dimensionless streamfunction formulation, the nonlinear variables for a 2D
simulations are solute concentration and streamfunction:

!listing examples/2D/isotropic/2DddcSF.i block=Variables label=False

In 3D, an additional streamfunction variable must also be added:

!listing examples/3D/isotropic/3DddcSF.i block=Variables label=False

### Materials

For the dimensional formulation, several material and fluid properties are required:
porosity, permeability, fluid density and viscosity, and diffusivity. These can be
added using the following Numbat materials:

!listing examples/2D/isotropic/2Dddc.i block=Materials label=False

!!! note
    No material properties are required in the dimensionless streamfunction formulation

### Kernels

Four kernels are required for a dimensional model: `NumbatTimeDerivative`, `NumbatDiffusion`, `NumbatConvection`, and `NumbatDarcy`.

!listing examples/2D/isotropic/2Dddc.i block=Kernels label=False

For the dimensionless streamfunction formulation, four kernels are required for a 2D model: a `NumbatDarcySF` kernel, a `NumbatDiffusionSF` kernel, a `NumbatConvectionSF` kernel, and a `TimeDerivative` kernel.

!listing examples/2D/isotropic/2DddcSF.i block=Kernels label=False

For 3D models, an additional `NumbatDarcySF` kernel is required for the
additional streamfunction variable. An example of the kernels block for
a 3D isotropic model is

!listing examples/3D/isotropic/3DddcSF.i block=Kernels label=False

In the 3D case, it is important to note that the `NumbatDarcySF` kernel must
specify the component that it applies to, and that the
`streamfunction` keyword in the `NumbatConvectionSF`
kernel must contain both streamfunction variables ordered by the `x`
component then the `y` component.

!!! note
    For the streamfunction formulation, a `TimeDerivative` kernel is used, rather than a `NumbatTimeDerivative` kernel, as porosity has been scaled out of the problem.

### Boundary conditions

Appropriate boundary conditions must be prescribed. Typically, these
will be constant concentration at the top of the model domain, periodic
boundary conditions on the lateral sides (to mimic an infinite
model), and no-flow boundary conditions at the top and bottom
surfaces.

In the 2D dimensional formulation, this can be achieved using the following input block:
!listing examples/2D/isotropic/2Dddc.i block=BCs label=False

while in 3D
!listing examples/3D/isotropic/3Dddc.i block=BCs label=False

In this case, the *conctop* boundary condition is a Dirichlet condition
at the top of the model that fixes the value of concentration.

It is useful to note that a MOOSE *GeneratedMesh* provides descriptive
names for the sides of the model (top, bottom, left, right) which can be
referenced in the input file.

For the dimensionless streamfunction formulation,
no-flow boundary conditions are prescribed
on the top and bottom surfaces by holding the *streamfunction* variable
constant (in this case 0).

!listing examples/2D/isotropic/2DddcSF.i block=BCs label=False

### Executioner

Each MOOSE simulation must use an *Executioner*, which provides
parameters for the solve.

!listing examples/2D/isotropic/2Dddc.i block=Executioner label=False

Executioners are a standard MOOSE feature that are well documented on
the [MOOSE], so no further detail is provided here.

### Preconditioning

A default preconditioning block is used that provides all Jacobian
entries to aid convergence.

!listing examples/2D/isotropic/2Dddc.i block=Preconditioning label=False

This is a standard MOOSE feature that is documented on the [MOOSE] website, so no further detail is provided here.

### Outputs

To provide ouptut from the simulation, an *Outputs* block must be
specified. An example is

!listing examples/2D/isotropic/2Dddc.i block=Outputs label=False

There are a large number of output options available in
MOOSE, see the [MOOSE] website for further details.

## Optional input

While the above required blocks will enable a Numbat simulation to run,
there are a number of optional input blocks that will improve the
simulations are increase the amount of rsults provided.

### Mesh modifier

It is often useful to bias the mesh so that the spatial resolution is more refined at the boundary where the solute enters the domain so that the small initial downwelling plumes can be accurately characterised. Numbat provides a mesh modifier, [NumbatBiasedMesh](/NumbatBiasedMesh.md), that allows the mesh to be refined to a specified spatial resolution at one boundary.

!listing examples/2D/isotropic/2Dddc.i block=MeshModifiers label=False

### Mesh adaptivity

MOOSE features built-in mesh adaptivity that is extremely useful in
Numbat simulations to reduce computational expense. This can be included using:

!listing examples/3D/isotropic/3DddcSF.i block=Adaptivity label=False

For details about mesh adaptivity, see the [MOOSE] website.

### Initial condition

To seed the instability, a random perturbation to the initial concentration can be prescribed using the `NumbatPerturbationIC` initial condition.

!listing examples/2D/isotropic/2DddcSF.i block=ICs label=False

The `NumbatPerturbationIC` initial condition applies the diffusive concentration profile to the nodes for (scaled) time $t = 1$,
\begin{equation}
c_d(z, t =1) = 1 + \mathrm{erf}(z /2),
\end{equation}
for $z < 0$, where $\mathrm{erf(z)}$ is the error function.

A uniform random perturbation is then added to the diffusive concentration profile, where the amplitude of the perturbation is specified by the input file value `amplitude`.

### Postprocessors

The flux over the top boundary or the total mass of solute in the model is of particular interest in many cases (especially convective mixing of CO$_2$). These can be
calculated at each time step using the [NumbatSideFlux](/NumbatSideFlux.md) and [NumbatTotalMass](/NumbatTotalMass.md) Postprocessors.

!listing examples/2D/isotropic/2Dddc.i block=Postprocessors label=False

Versions of these Postprocessors for the dimensionless streamfunction formulation are also
provided, see [NumbatSideFluxSF](/NumbatSideFluxSF.md) and [NumbatTotalMassSF](/NumbatTotalMassSF.md) for details.

Numbat also provides a simple Postprocessor to calculate the Rayleigh number for
dimensional simulations, see [NumbatRayleighNumber](/NumbatRayleighNumber.md) for details.

### AuxKernels

The velocity components in the $x$ and $y$ directions (in 2D), and $x$,
$y$, and $z$ directions in 3D can be calculated using the auxiliary
system. These velocity components are calculated using the
streamfunction(s), see the governing equations for details.

In the 2D case, two auxiliary variables, $u$ and $w$, can be defined for
the horizontal and vertical velocity components, respectively.

!!! note
    Importantly, these auxiliary variables **must** have monomial
    shape functions (these are referred to as *elemental* variables, as the
    value is constant over each mesh element). This restriction is due to fact
    that the gradient of variables is undefined for
    *nodal* auxiliary variables (for example, those using linear Lagrange
    shape functions).

An example of the input syntax for the 2D case is

!listing examples/2D/isotropic/2DddcSF.i block=AuxVariables label=False

For the 3D case, there is an additional horizontal velocity component
(*v*), so the input syntax is

!listing examples/3D/isotropic/3DddcSF.i block=AuxVariables label=False

The velocity components are calculated by [NumbatDarcyVelocity](/NumbatDarcyVelocity.md) AuxKernels (or [NumbatDarcyVelocitySF](/NumbatDarcyVelocitySF.md) AuxKernels for the
dimensionless streamfunction formulation). Each velocity component is computed by an
AuxKernel.

For the 2D case, two AuxKernels are required:
!listing examples/2D/isotropic/2DddcSF.i block=AuxKernels label=False

while for 3D, three AuxKernels are necessary:
!listing examples/3D/isotropic/3DddcSF.i block=AuxKernels label=False

!!! note
    For the 3D case, both streamfunction variables must be given, in the correct order (eg. $x$ then $y$)
