# This input file is used in the documentation. Please do not alter the
# ordering of these blocks

[Mesh]
  type = GeneratedMesh
  dim = 2
  ymin = -100
  ymax = 0
  ny = 20
  nz = 0
  bias_y = 0.75
[]

[Variables]
  [./concentration]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0.0
  [../]
  [./streamfunction]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0.0
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

[AuxKernels]
  [./uAux]
    type = NumbatDarcyVelocitySF
    variable = u
    component = x
    streamfunction = streamfunction
  [../]
  [./vAux]
    type = NumbatDarcyVelocitySF
    variable = v
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

[Executioner]
  type = Transient
  end_time = 100
  solve_type = PJFNK
  petsc_options_iname = '-ksp_type -pc_type -pc_sub_type'
  petsc_options_value = 'gmres asm lu'
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Outputs]
  perf_graph = true
  [./csvoutput]
    type = CSV
    file_base = 2DSF
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
