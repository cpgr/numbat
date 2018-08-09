# Density-driven convective mixing using the streamfunction formulation

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 1000
  ymin = -500
  ymax = 0
  nx = 80
  ny = 25
  bias_y = 0.9
[]

[Adaptivity]
  marker = errormarker
  max_h_level = 1
  [./Indicators]
    [./gradjumpindicator]
      type = GradientJumpIndicator
      variable = concentration
    [../]
  [../]
  [./Markers]
    [./errormarker]
      type = ErrorToleranceMarker
      refine = 0.005
      indicator = gradjumpindicator
    [../]
  [../]
[]

[Variables]
  [./concentration]
    order = FIRST
    family = LAGRANGE
  [../]
  [./streamfunction]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0.0
  [../]
[]

[ICs]
  [./concentration]
    type = NumbatPerturbationIC
    variable = concentration
    amplitude = 0.1
    seed = 1
  [../]
[]

[Kernels]
  [./Darcy]
    type = NumbatDarcySF
    variable = streamfunction
    concentration = concentration
  [../]
  [./Convection]
    type = NumbatConvectionSF
    variable = concentration
    streamfunction = streamfunction
  [../]
  [./Diffusion]
    type = NumbatDiffusionSF
    variable = concentration
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
  [./w]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./uAux]
    type = NumbatDarcyVelocitySF
    variable = u
    component = x
    streamfunction = streamfunction
  [../]
  [./wAux]
    type = NumbatDarcyVelocitySF
    variable = w
    component = y
    streamfunction = streamfunction
  [../]
[]

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
  [./Periodic]
    [./x]
      variable = 'concentration streamfunction'
      auto_direction = x
    [../]
  [../]
[]

[Executioner]
  type = Transient
  dtmax = 100
  end_time = 5000
  start_time = 1
  solve_type = PJFNK
  nl_abs_tol = 1e-10
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
    type = NumbatSideFluxSF
    variable = concentration
    boundary = top
  [../]
  [./numdofs]
    type = NumDOFs
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
    petsc_options = -snes_ksp_ew
    petsc_options_iname = '-pc_type -sub_pc_type -ksp_atol'
    petsc_options_value = 'asm ilu 1e-12'
  [../]
[]

[Outputs]
  perf_graph = true
  [./exodus]
    type = Exodus
    file_base = 2DddcSF
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  [./csvoutput]
    type = CSV
    file_base = 2DddcSF
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
