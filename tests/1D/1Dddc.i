[Mesh]
  type = GeneratedMesh
  dim = 1
  xmax = 10
  nx = 20
  nz = 0
[]

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
    streamfunction_variable = streamfunction
  [../]
  [./wAux]
    type = NumbatDarcyVelocitySF
    variable = w
    component = y
    streamfunction_variable = streamfunction
  [../]
[]

[BCs]
  [./conctop]
    type = DirichletBC
    variable = concentration
    boundary = top
    value = 1.0
  [../]
  [./concbottom]
    type = DirichletBC
    variable = concentration
    boundary = bottom
    value = 0.0
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
  end_time = 100
  solve_type = PJFNK
  petsc_options_iname = '-ksp_type -pc_type -pc_sub_type'
  petsc_options_value = 'gmres asm lu'
[]

[Postprocessors]
  [./boundaryfluxint]
    type = SideFluxIntegral
    variable = concentration
    boundary = top
    diffusivity = 1
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Outputs]
  [./console]
    type = Console
    perf_log = true
    output_nonlinear = true
  [../]
[]
