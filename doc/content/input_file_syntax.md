# Input file syntax

The input file for a Numbat simulation is a simple, block-structured
text file based on the input files for a plain [MOOSE] input file.

## Essential input

Details of the minimum input file requirements are given below.

### Mesh

All simulations must feature a mesh. For the basic model with a
rectangular mesh, the built-in [NumbatBiasedMesh](/NumbatBiasedMesh.md) can be used to
create a suitable mesh. This is a type of [GeneratedMesh](/GeneratedMesh.md) that provides the
option to refine the mesh near one boundary. The size of the initial element can be specified,
after which the elements are progressively coarser, see [NumbatBiasedMesh](/NumbatBiasedMesh.md)
for details. This can be extremely useful in simulations of density-driven convection, where
it is necessary to have a finer mesh in the vicinity of the boundary where the fingers form in
order to capture the process adequately. Away from this region, the fingers grow and merge, so
that a coarser mesh is sufficient to simulate them. Having a biased mesh such as that produced by [NumbatBiasedMesh](/NumbatBiasedMesh.md) can minimise the number of elements necessary,
reducing the overall computational demands.

In 2D, the input block looks like:

!listing examples/inputfiles/2D.i block=Mesh

In 3D, the Mesh block would look like:

!listing examples/inputfiles/3D.i block=Mesh

!alert note
In contrast to the normal [GeneratedMesh](/GeneratedMesh.md) provided by MOOSE, [NumbatBiasedMesh](/NumbatBiasedMesh.md) renames the boundaries of the three dimensional
mesh so that the boundaries `top` and `bottom` are at the extrema of the `z` axis.

### Variables

The number and type of variables required depends on the chosen formulation. For the
dimensional formulation, two nonlinear variables must be provided, representing the fluid pressure and solute concentration.

!listing examples/inputfiles/2D.i block=Variables

For the dimensionless streamfunction formulation, the nonlinear variables for a 2D
simulations are solute concentration and streamfunction:

!listing examples/inputfiles/2DSF.i block=Variables

In 3D, an additional streamfunction variable must also be added:

!listing examples/inputfiles/3DSF.i block=Variables

### Materials

For the dimensional formulation, several material and fluid properties are required:
porosity, permeability, fluid density and viscosity, and diffusivity. These can be
added using the following Numbat materials:

!listing examples/inputfiles/2D.i block=Materials

!alert note
No material properties are required in the dimensionless streamfunction formulation

### Kernels

Four kernels are required for a dimensional model: [NumbatTimeDerivative](/NumbatTimeDerivative.md), [NumbatDiffusion](/NumbatDiffusion.md), [NumbatConvection](/NumbatConvection.md), and [NumbatDarcy](/NumbatDarcy.md).

!listing examples/inputfiles/2D.i block=Kernels

For the dimensionless streamfunction formulation, four kernels are required for a 2D model: a [NumbatDarcySF](/NumbatDarcySF.md) kernel, a [NumbatDiffusionSF](/NumbatDiffusionSF.md) kernel, a [NumbatConvectionSF](/NumbatConvectionSF.md) kernel, and a [TimeDerivative](/TimeDerivative.md) kernel.

!listing examples/inputfiles/2DSF.i block=Kernels

For 3D models, an additional [NumbatDarcySF](/NumbatDarcySF.md) kernel is required for the
additional streamfunction variable. An example of the kernels block for
a 3D isotropic model is

!listing examples/inputfiles/3DSF.i block=Kernels

In the 3D case, it is important to note that the [NumbatDarcySF](/NumbatDarcySF.md) kernel must
specify the component that it applies to, and that the
`streamfunction` keyword in the [NumbatConvectionSF](/NumbatConvectionSF.md)
kernel must contain both streamfunction variables ordered by the `x`
component then the `y` component.

!alert note
For the streamfunction formulation, a [TimeDerivative](/TimeDerivative.md) kernel is used, rather than a [NumbatTimeDerivative](/NumbatTimeDerivative.md) kernel, as porosity has been scaled out of the problem.

### Boundary conditions

Appropriate boundary conditions must be prescribed. Typically, these
will be constant concentration at the top of the model domain, periodic
boundary conditions on the lateral sides (to mimic an infinite
model), and no-flow boundary conditions at the top and bottom
surfaces.

In the 2D dimensional formulation, this can be achieved using the following input block:

!listing examples/inputfiles/2D.i block=BCs

while in 3D

!listing examples/inputfiles/3D.i block=BCs

In this case, the `conctop` boundary condition fixes the value of concentration at  the top boundary, while the `Periodic` boundary condition enforces periodicity of concentration along
the boundaries in the directions specified in the `auto_direction` parameter.

It is useful to note that a MOOSE [GeneratedMesh](/GeneratedMesh.md) provides descriptive
names for the sides of the model (top, bottom, left, right) which can be
referenced in the input file.

For the dimensionless streamfunction formulation,
no-flow boundary conditions are prescribed
on the top and bottom surfaces by holding the `streamfunction` variable
constant (in this case 0).

!listing examples/inputfiles/2DSF.i block=BCs

### Executioner

Each MOOSE simulation must use an `Executioner`, which provides
parameters for the solve.

!listing examples/inputfiles/2D.i block=Executioner

Executioners are a standard MOOSE feature that are well documented on
the [MOOSE], so no further detail is provided here.

### Preconditioning

A default preconditioning block is used that provides all Jacobian
entries to aid convergence.

!listing examples/inputfiles/2D.i block=Preconditioning

This is a standard MOOSE feature that is documented on the [MOOSE] website, so no further detail is provided here.

### Outputs

To provide ouptut from the simulation, an `Outputs` block must be
specified. An example is

!listing examples/inputfiles/2D.i block=Outputs

There are a large number of output options available in
MOOSE, see the [MOOSE] website for further details.

## Action system

To avoid having to enter several of these input file blocks each time, and ensuring
that the correct parameters are provided to each object in the correct order, Numbat
provides some powerful actions that automatically add most of the required objects.

The [NumbatAction](/NumbatAction.md) adds all of the nonlinear variables, kernels, aux
variables, aux kernels and postprocessors typically required in a dimensional Numbat simulation.

This action is called in the input file simply as

!listing tests/2D/2D_action.i block=Numbat

The use of this action is exactly equivalent to the following input file syntax

!listing tests/2D/2D.i start=Variables end=Materials

A specific value for the saturated boundary concentration can optionally be provided

!listing tests/2D/2D_c0_action.i block=Numbat

Similarly, the [NumbatSFAction](/NumbatSFAction.md) adds all of the nonlinear variables, kernels,
aux variables, aux kernels and postprocessors typically required in a dimensionless Numbat simulation.

This action is called in the input file simply as

!listing tests/2D/2DSF_action.i block=Numbat

The use of this action is exactly equivalent to the following input file syntax for a 2D
simulation.

!listing tests/2D/2DSF.i start=Variables end=Executioner

The use of these actions is recommended for all users, as they reduce the possibility of input
file errors.

## Optional input

While the above required blocks will enable a Numbat simulation to run,
there are a number of optional input blocks that will improve the
simulations are increase the amount of results provided.

### Mesh adaptivity

MOOSE features built-in mesh adaptivity that is extremely useful in
Numbat simulations to reduce computational expense. This can be included using:

!listing examples/inputfiles/3DSF.i block=Adaptivity

For details about mesh adaptivity, see the [MOOSE] website.

### Initial condition

To seed the instability, a random perturbation to the initial concentration can be prescribed using the [NumbatPerturbationIC](/NumbatPerturbationIC.md) initial condition.

!listing examples/inputfiles/2DSF.i block=ICs

The [NumbatPerturbationIC](/NumbatPerturbationIC.md) initial condition applies the diffusive concentration profile to the nodes for (scaled) time $t = 1$,
\begin{equation}
c_d(z, t =1) = 1 + \mathrm{erf}(z /2),
\end{equation}
for $z < 0$, where $\mathrm{erf(z)}$ is the error function.

A uniform random perturbation is then added to the diffusive concentration profile, where the amplitude of the perturbation is specified by the input file value `amplitude`.

### Postprocessors

The flux over the top boundary or the total mass of solute in the model is of particular interest in many cases (especially convective mixing of CO$_2$). These can be
calculated at each time step using the [NumbatSideFlux](/NumbatSideFlux.md) and [NumbatTotalMass](/NumbatTotalMass.md) Postprocessors.

!listing examples/inputfiles/2D.i block=Postprocessors

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

!alert note
Importantly, these auxiliary variables +must+ have monomial
shape functions (these are referred to as elemental variables, as the
value is constant over each mesh element). This restriction is due to fact
that the gradient of variables is undefined for
nodal auxiliary variables (for example, those using linear Lagrange
shape functions).

An example of the input syntax for the 2D case is

!listing examples/inputfiles/2DSF.i block=AuxVariables

For the 3D case, there is an additional horizontal velocity component
(`v`), so the input syntax is

!listing examples/inputfiles/3DSF.i block=AuxVariables

The velocity components are calculated by [NumbatDarcyVelocity](/NumbatDarcyVelocity.md) AuxKernels (or [NumbatDarcyVelocitySF](/NumbatDarcyVelocitySF.md) AuxKernels for the
dimensionless streamfunction formulation). Each velocity component is computed by an
AuxKernel.

For the 2D case, two AuxKernels are required:

!listing examples/inputfiles/2DSF.i block=AuxKernels

while for 3D, three AuxKernels are necessary:

!listing examples/inputfiles/3DSF.i block=AuxKernels

!alert note
For the 3D case, both streamfunction variables must be given, in the correct order (eg. $x$ then $y$)
