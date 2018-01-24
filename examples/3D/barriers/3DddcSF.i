# Density-driven convective mixing in a 3D model using the streamfunction
# formulation
#
# Ra = 5000
[Mesh]
  type = FileMesh
  file = barrier.msh
  parallel_type = REPLICATED
[]

[Variables]
  [./concentration]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = NumbatPerturbationIC
      variable = concentration
      amplitude = 0.1
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
  [./Darcy_x]
    type = NumbatDarcySF
    variable = streamfunctionx
    component = x
    concentration = 'concentration'
  [../]
  [./Darcy_y]
    type = NumbatDarcySF
    variable = streamfunctiony
    component = y
    concentration = 'concentration'
  [../]
  [./Convection]
    type = NumbatConvectionSF
    variable = concentration
    streamfunction = 'streamfunctionx streamfunctiony'
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
    type = NumbatDarcyVelocitySF
    variable = u
    component = x
    streamfunction = 'streamfunctionx streamfunctiony'
  [../]
  [./vAux]
    type = NumbatDarcyVelocitySF
    variable = v
    component = y
    streamfunction = 'streamfunctionx streamfunctiony'
  [../]
  [./wAux]
    type = NumbatDarcyVelocitySF
    variable = w
    component = z
    streamfunction = 'streamfunctionx streamfunctiony'
  [../]
[]

[BCs]
  [./conctop]
    type = DirichletBC
    variable = concentration
    boundary = 'top'
    value = 1.0
  [../]
  [./streamfunxtop]
    type = DirichletBC
    variable = streamfunctionx
    boundary = 'top'
    value = 0.0
  [../]
  [./streamfunxbottom]
    type = DirichletBC
    variable = streamfunctionx
    boundary = 'bottom'
    value = 0.0
  [../]
  [./streamfunytop]
    type = DirichletBC
    variable = streamfunctiony
    boundary = 'top'
    value = 0.0
  [../]
  [./streamfunybottom]
    type = DirichletBC
    variable = streamfunctiony
    boundary = 'bottom'
    value = 0.0
  [../]
  [./Periodic]
    [./xy]
      variable = 'concentration streamfunctionx streamfunctiony'
      auto_direction = 'x y'
    [../]
  [../]
  [./streamfunxbarrier]
    type = PresetBC
    variable = streamfunctionx
    boundary = 'barriers'
    value = 0
  [../]
  [./streamfunybarrier]
    type = PresetBC
    variable = streamfunctiony
    boundary = 'barriers'
    value = 0
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
    petsc_options = '-snes_ksp_ew'
    petsc_options_iname = '-ksp_type -pc_type -pc_asm_overlap -sub_pc_type -pc_factor_levels -ksp_atol'
    petsc_options_value = 'gmres asm 10 ilu 4 1e-12'
  [../]
[]

[Executioner]
  type = Transient
  end_time = 6e4
  start_time = 1
  solve_type = NEWTON
  nl_abs_tol = 1e-9
  l_max_its = 200
  [./TimeStepper]
    type = FunctionDT
    interpolate = false
    time_t = '0 10 500 1e3 1e4 6e4'
    time_dt = '9 10 50 100 200 200'
  [../]
[]

[Postprocessors]
  [./boundaryfluxint]
    type = NumbatSideFluxSF
    variable = 'concentration'
    boundary = 'top'
    execute_on = 'TIMESTEP_END INITIAL'
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
    execute_on = 'INITIAL TIMESTEP_END'
    interval = 4
  [../]
  [./csvoutput]
    type = CSV
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  [./checkpoint]
    type = Checkpoint
    num_files = 2
    interval = 10
  [../]
[]
