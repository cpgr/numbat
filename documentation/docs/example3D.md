# 3D example

A working example of a 3D problem can be found at [https://github.com/cpgr/numbat/blob/master/examples/3D/isotropic/3Dddc.i](https://github.com/cpgr/numbat/blob/master/examples/3D/isotropic/3Dddc.i).


## Input file

The complete input file for this problem is

    [Mesh]
      type = GeneratedMesh
      dim = 3
      xmax = 500
      ymax = 500
      zmin = -200
      zmax = 0
      nx = 40
      ny = 40
      nz = 20
      bias_z = 0.7
    []

    [Adaptivity]
      max_h_level = 1
      initial_marker = boxmarker
      initial_steps = 1
      marker = combomarker
      [./Indicators]
        [./gradjumpindicator]
          type = GradientJumpIndicator
          variable = concentration
        [../]
      [../]
      [./Markers]
        [./errormarker]
          type = ErrorToleranceMarker
          refine = 0.05
          indicator = gradjumpindicator
        [../]
        [./boxmarker]
          type = BoxMarker
          bottom_left = '0 0 -10'
          top_right = '500 500 0'
          inside = refine
          outside = dont_mark
        [../]
        [./combomarker]
          type = ComboMarker
          markers = 'boxmarker errormarker'
        [../]
      [../]
    []

    [Variables]
      [./concentration]
        order = FIRST
        family = LAGRANGE
        [./InitialCondition]
          type = PerturbationIC
          variable = concentration
          amplitude = 0.02
          seed = 1
        [../]
      [../]
      [./streamfunctionx]
        order = FIRST
        family = LAGRANGE
        initial_condition = 0.0
      [../]
      [./streamfunctiony]
        order = FIRST
        family = LAGRANGE
        initial_condition = 0.0
      [../]
    []

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
      [./ThreeDConvectionDiffusionDDC]
        type = ConvectionDiffusionDDC
        variable = concentration
        streamfunction_variable = 'streamfunctionx streamfunctiony'
        coeff_tensor = '1 0 0 0 1 0 0 0 1'
      [../]
      [./TimeDerivative]
        type = TimeDerivative
        variable = concentration
      [../]
    []

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

    [AuxKernels]
      [./uAux]
        type = VelocityDDCAux
        variable = u
        component = x
        streamfunction_variable = 'streamfunctionx streamfunctiony'
      [../]
      [./vAux]
        type = VelocityDDCAux
        variable = v
        component = y
        streamfunction_variable = 'streamfunctionx streamfunctiony'
      [../]
      [./wAux]
        type = VelocityDDCAux
        variable = w
        component = z
        streamfunction_variable = 'streamfunctionx streamfunctiony'
      [../]
    []

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

    [Preconditioning]
      [./smp]
        type = SMP
        full = true
      [../]
    []

    [Executioner]
      type = Transient
      dtmax = 100
      end_time = 2500
      start_time = 1
      solve_type = PJFNK
      nl_abs_tol = 1e-10
      petsc_options = -snes_ksp_ew
      [./TimeStepper]
        type = IterationAdaptiveDT
        dt = 1
        cutback_factor = 0.5
        growth_factor = 2
      [../]
      [./TimeIntegrator]
        type = LStableDirk2
      [../]
    []

    [Postprocessors]
      [./boundaryfluxint]
        type = SideFluxIntegral
        variable = concentration
        boundary = front
        diffusivity = 1
      [../]
      [./numdofs]
        type = NumDOFs
      [../]
    []

    [Outputs]
      [./console]
        type = Console
        perf_log = true
        output_nonlinear = true
        output_linear = true
      [../]
      [./exodus]
        type = Exodus
        file_base = 3Dddc
        execute_on = 'INITIAL TIMESTEP_END'
      [../]
      [./csvoutput]
        type = CSV
        file_base = 3Dddc
        execute_on = 'INITIAL TIMESTEP_END'
      [../]
    []

## Running the example

**Note:** This example should **not** be run on a laptop or workstation due to the large computational requirements. Do **not** run this using the *Peacock* gui provided by MOOSE.

Examples of the total run times for this problem on a cluster are over 27 hours for a single processor down to only 30 minutes using 100 processors in parallel.

## Results

This 3D example should produce a concentration profile similar to that presented in Figure @fig:3D, where several downwelling plumes of high concentration can be observed:

![3D concentration profile](images/3D.png){#fig:3D}

<br>
Note that due to the random perturbation applied to the initial concentration profile, the geometry of the concentration profile obtained will differ from run to run.

The flux over the top surface is of particular interest in many cases (especially convective mixing of $\textrm{CO}_2$). This is calculated in this example file using the *boundaryfluxint* postprocessor in the input file, and presented in Figure @fig:3Dflux.

![3D flux across the top boundary](images/3Dflux.png){#fig:3Dflux}

<br>
Initially, the flux is purely diffusive, and scales as $1 / \sqrt(\pi t)$, where $t$ is time (shown as the dashed green line). After some time, the convective instability becomes sufficiently strong, at which point the flux across the top boundary rapidly increases (at a time of approximately 1,700 seconds). Also shown for comparison is the flux for the 2D example. It is apparent that the 3D model leads in a slower onset of convection (the time where the flux first increases from the diffusive rate).
