# Input file syntax

The input file for a Numbat simulation is a simple, block-structured
text file.

A working example of a 2D problem can be found at
<https://github.com/cpgr/numbat/blob/master/examples/2D/2Dddc.i>

A working example of a 3D problem can be found at
<https://github.com/cpgr/numbat/blob/master/examples/3D/3Dddc.i>

## Essential input

Details of the minimum input file requirements are given below.

### Mesh

All simulations must feature a mesh. For the basic model with a
rectangular mesh, the built-in MOOSE *GeneratedMesh* can be used to
create a suitable mesh. In 2D, the input block looks like:

    [Mesh]
      type = GeneratedMesh
      dim = 2
      xmax = 1000
      ymin = -200
      ymax = 0
      nx = 80
      ny = 20
      bias_y = 0.7
    []

This creates a 2D mesh from $x = 0$ to $x = 1000$ and $y = -200$ to
$y = 0$ with 80 elements in the $x$-direction and 20 elements in the
$y$-direction. It is useful to have a mesh that is more refined at the
top of the model, to accurately capture the initially small structure of
the convective fingers. This is achieved using the built-in *bias\_y*
parameter.

In 3D, the Mesh block would look like:

    [Mesh]
      type = GeneratedMesh
      dim = 3
      xmax = 200
      ymax = 200
      zmin = -200
      zmax = 0
      nx = 10
      ny = 10
      nz = 10
      bias_z = 0.7
    []

Again, the mesh is refined at the top of the model using the the
*bias\_z* parameter.

### Variables

For a 2D model, the simulation must have two variables: *concentration*
and *streamfunction*. This can be implemented in the input file using
the following code:

    [Variables]
    [./concentration]
    order = FIRST
    family = LAGRANGE
      [./InitialCondition]
        type = NumbatPerturbationIC
        variable = concentration
        amplitude = 0.01
        seed = 1
      [../]
    [../]
    [./streamfunction]
      order = FIRST
      family = LAGRANGE
      initial_condition = 0.0
    [../]
    []

Initial conditions can also be specified in the *Variables* block. In
this case, the initial concentration is perturbed using a
*NumbatPerturbationIC* to seed the instability.

For a 3D model, three variables are required: one *concentration*
variable and two *streamfunction* variables corresponding to the *x* and
*y* components. This can be implemented in the input file using:

    [Variables]  
      [./concentration]  
      [../]  
      [./streamfunctionx]  
      [../]  
      [./streamfunctiony]  
      [../]  
    []    

### Kernels

Three kernels are required for a 2D model: a *DarcyDDC* kernel for the
*streamfunction* variable, a *NumbatConvectionDiffusionSF* kernel for the
*concentration* variable, and a *TimeDerivative* kernel also for the
*concentration* variable. An example for an isotropic model is

    [Kernels]
      [./TwoDDarcyDDC]
        type = DarcyDDC
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

For 3D models, an additional *DarcyDDC* kernel is required for the
additional stream function variable. An example of the kernels block for
a 3D isotropic model is

    [Kernels]
      [./ThreeDDarcyDDCx]
        type = DarcyDDC
        variable = streamfunctionx
        concentration_variable = concentration
        component = x
      [../]
      [./ThreeDDarcyDDCy]
        type = DarcyDDC
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

In the 3D case, it is important to note that the *DarcyDDC* kernel must
specify the component that it applies to, and that the
*streamfunction\_variable* keyword in the *NumbatConvectionDiffusionSF*
kernel must contain both *streamfunction* variables ordered by the *x*
component then the *y* component.

### Initial condition

To seed the instability, a random perturbation to the initial concentration is prescribed using the *NumbatPerturbationIC* initial condition. This can be applied in the *Variables* block in the input file (see above) using

    [./InitialCondition]
      type = NumbatPerturbationIC
      variable = concentration
      amplitude = 0.01
      seed = 1
    [../]

The *NumbatPerturbationIC* initial condition applies the diffusive concentration profile to the nodes for (scaled) time $t = 1$,
\begin{equation}
c_d(z, t =1) = 1 + \mathrm{erf}(z /2),
\end{equation}
for $z < 0$, where $\mathrm{erf(z)}$ is the error function.

A uniform random perturbation is then added to the diffusive concentration profile, where the amplitude of the perturbation is specified by the input file value *amplitude*.

### Boundary conditions

Appropriate boundary conditions must be prescribed. Typically, these
will be constant concentration at the top of the model domain, periodic
boundary conditions on the lateral sides (to mimic an infinite
reservoir), and no-flow boundary conditions at the top and bottom
surfaces.

In 2D, this can be achieved using the following input block:

    [BCs]
      [./conctop]
        type = DirichletBC
        variable = concentration
        boundary = top
        value = 1.0
      [../]
      [./streamfuntop]
        type = DirichletBC
        variable = streamfunction
        boundary = top
        value = 0.0
      [../]
      [./streamfunbottom]
        type = DirichletBC
        variable = streamfunction
        boundary = bottom
        value = 0.0
      [../]
      [./periodic]
        [./x]
          variable = 'concentration streamfunction'
          auto_direction = x
        [../]
      [../]
    []

In this case, the *conctop* boundary condition is a Dirichlet condition
at the top of the model that fixes the value of concentration to unity.
It is useful to note that a MOOSE *GeneratedMesh* provides descriptive
names for the sides of the model (top, bottom, left, right) which can be
referenced in the input file. No-flow boundary conditions are prescribed
on the top and bottom surfaces by holding the *streamfunction* variable
constant (in this case 0). Finally, periodic boundary conditions are
applied by the *periodic* block, which specifies that both the
*concentration* and *streamfunction* variables are periodic on
boundaries in the $x$-direction.

A similar boundary condition block is used in 3D, except that no-flow
boundaries must be imposed on both streamfunction variables, see below:

    [BCs]
      [./conctop]
        type = DirichletBC
        variable = concentration
        boundary = front
        value = 1.0
      [../]
      [./streamfunxtop]
        type = DirichletBC
        variable = streamfunctionx
        boundary = front
        value = 0.0
      [../]
      [./streamfunxbottom]
        type = DirichletBC
        variable = streamfunctionx
        boundary = back
        value = 0.0
      [../]
      [./streamfunytop]
        type = DirichletBC
        variable = streamfunctiony
        boundary = front
        value = 0.0
      [../]
      [./streamfunybottom]
        type = DirichletBC
        variable = streamfunctiony
        boundary = back
        value = 0.0
      [../]
      [./Periodic]
        [./xy]
          variable = 'concentration streamfunctionx streamfunctiony'
          auto_direction = 'x y'
        [../]
      [../]
    []

### Executioner

Each MOOSE simulation must use an *Executioner*, which provides
parameters for the solve. In both 2D and 3D models, a transient
*Executioner* is used, an example of which is presented below:

    [Executioner]
      type = Transient
      scheme = bdf2
      dtmin = 0.1
      dtmax = 200
      end_time = 2000
      solve_type = PJFNK
      petsc_options_iname = '-ksp_type -pc_type -pc_sub_type'
      petsc_options_value = 'gmres asm ilu'
      [./TimeStepper]
        type = IterationAdaptiveDT
        dt = 1
        cutback_factor = 0.5
        growth_factor = 2
      [../]
    []

*Executioners* are a standard MOOSE feature that are well documented on
the [MOOSE website](http://www.mooseframework.com), so no further detail
is provided here.

### Preconditioning

A default preconditioning block is used that provides all Jacobian
entries to aid convergence. This is identical for both 2D and 3D models:

    [Preconditioning]
      [./smp]
        type = SMP
        full = true
      [../]
    []

This is a standard MOOSE feature that is documented on the [MOOSE
website](http://www.mooseframework.com), so no further detail is
provided here.

### Outputs

To provide ouptut from the simulation, an *Outputs* block must be
specified. An example is

    [Outputs]
      [./console]
        type = Console
        perf_log = true
        output_nonlinear = true
      [../]
      [./exodus]
        type = Exodus
        file_base = filename
        execute_on = 'INITIAL TIMESTEP_END FINAL'
      [../]
    []

In this case, some output regarding the iterations is streamed to the
console, while the results are provided in an Exodus file named
*filename.e*. There are a large number of output options available in
MOOSE, see the [MOOSE website](http://www.mooseframework.com) for
further details.

## Optional input

While the above required blocks will enable a Numbat simulation to run,
there are a number of optional input blocks that will improve the
simulations are increase the amount of rsults provided.

### Mesh adaptivity

MOOSE features built-in mesh adaptivity that is extremely useful in
Numbat simulations. This can be included using:

    [Adaptivity]
      marker = combomarker
      max_h_level = 2
      initial_marker = boxmarker
      initial_steps = 1
      [./Indicators]
        [./gradjumpindicator]
          type = GradientJumpIndicator
          variable = concentration
        [../]
      [../]
      [./Markers]
        [./errormarker]
          type = ErrorToleranceMarker
          coarsen = 0.0025
          refine = 0.005
          indicator = gradjumpindicator
        [../]
        [./boxmarker]
          type = BoxMarker
          bottom_left = '0 -1.0 0'
          top_right = '1000 0 0'
          inside = refine
          outside = dont_mark
        [../]
        [./combomarker]
          type = ComboMarker
          markers = 'boxmarker errormarker'
        [../]
      [../]
    []

For details about mesh adaptivity, see the [MOOSE
website](http://www.mooseframework.com).

### Flux at the top boundary

The flux over the top boundary is of particular interest in many cases
(especially convective mixing of $\textrm{CO}_2$). This can be
calculated at each time step using a *Postprocessor*:

    [Postprocessors]
      [./boundaryfluxint]
        type = SideFluxIntegral
        variable = concentration
        boundary = top
        diffusivity = 1
      [../]
    []

The output of the *Postprocessor* can be saved to a *csv* file by
including the following additional sub-block in the *Outputs* block:

    [./csvoutput]
      type = CSV
      file_base = filename
      execute_on = 'INITIAL TIMESTEP_END FINAL'
    [../]  

### Velocity components

The velocity components in the $x$ and $y$ directions (in 2D), and $x$,
$y$, and $z$ directions in 3D can be calculated using the auxiliary
system. These velocity components are calculated using the
streamfunction(s), see the governing equations for details.

In the 2D case, two auxiliary variables, $u$ and $w$, can be defined for
the horizontal and vertical velocity components, respectively.
Importantly, these auxiliary variables **must** have constant monomial
shape functions (these are referred to as *elemental* variables, as the
value is constant over each mesh element). This restriction is due to
the gradient of the streamfunction variable(s) being undefined for
*nodal* auxiliary variables (for example, those using linear Lagrange
shape functions). An example of the input syntax for the 2D case is

    [AuxVariables]
      [./u]
        order = CONSTANT
        family = MONOMIAL
      [../]
      [./w]
        order = CONSTANT
        family = MONOMIAL
      [../]
    []

For the 3D case, there is an additional horizontal velocity component
(*v*), so the input syntax is

    [AuxVariables]
      [./u]
        order = CONSTANT
        family = MONOMIAL
      [../]
      [./v]
        order = CONSTANT
        family = MONOMIAL
      [../]
      [./w]
        order = CONSTANT
        family = MONOMIAL
      [../]
    []

The velocity components are calculated by *NumbatDarcyVelocitySF* AuxKernels,
one for each component. For the 2D case, the input syntax is

    [AuxKernels]
      [./uAux]
        type = NumbatDarcyVelocitySF
        variable = u
        component = x
        streamfunction_variable = streamfunction
      [../]
      [./wAux]
        type = NumbatDarcyVelocitySF
        variable = w
        component = y
        streamfunction_variable = streamfunction
      [../]
    []

For the 3D case, three AuxKernels are required. Note that both
streamfunction variables must be given, in the correct order ($x$ then
$y$). An example of the input syntax is

    [AuxKernels]
      [./uAux]
        type = NumbatDarcyVelocitySF
        variable = u
        component = x
        streamfunction_variable = 'streamfunctionx streamfunctiony'
      [../]
      [./vAux]
        type = NumbatDarcyVelocitySF
        variable = v
        component = y
        streamfunction_variable = 'streamfunctionx streamfunctiony'
      [../]
      [./wAux]
        type = NumbatDarcyVelocitySF
        variable = w
        component = z
        streamfunction_variable = 'streamfunctionx streamfunctiony'
      [../]
    []
