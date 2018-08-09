[Mesh]
  type = NumbatBiasedMesh
  dim = 3
  xmax = 10
  ymax = 10
  zmin = -100
  zmax = 0
  nx = 1
  ny = 1
  nz = 10
  refined_edge = top
  refined_resolution = 1
[]

[Variables]
  [./concentration]
    order = FIRST
    family = LAGRANGE
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
    concentration = concentration
    component = x
  [../]
  [./Darcy_y]
    type = NumbatDarcySF
    variable = streamfunctiony
    concentration = concentration
    component = y
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
    boundary = top
    value = 1.0
  [../]
  [./streamfunxtop]
    type = DirichletBC
    variable = streamfunctionx
    boundary = top
    value = 0.0
  [../]
  [./streamfunxbottom]
    type = DirichletBC
    variable = streamfunctionx
    boundary = bottom
    value = 0.0
  [../]
  [./streamfunytop]
    type = DirichletBC
    variable = streamfunctiony
    boundary = top
    value = 0.0
  [../]
  [./streamfunybottom]
    type = DirichletBC
    variable = streamfunctiony
    boundary = bottom
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
  end_time = 100
  solve_type = PJFNK
[]

[Postprocessors]
  [./boundary_flux]
    type = NumbatSideFluxSF
    variable = concentration
    boundary = top
  [../]
  [./total_mass]
    type = NumbatTotalMassSF
    variable = concentration
  [../]
[]

[Outputs]
  perf_graph = true
  [./csvoutput]
    type = CSV
    file_base = 3DSF
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
