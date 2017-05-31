# Tests the NumbatDarcy kernel with a steady executioner

[GlobalParams]
  gravity = '0 0 0'
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 20
  ymax = 10
  nx = 10
  ny = 1
[]

[Variables]
  [./pressure]
  [../]
[]

[AuxVariables]
  [./concentration]
    initial_condition = 0.1
  [../]
  [./u]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[AuxKernels]
  [./u]
    type = DarcyVelocityAux
    pressure = pressure
    variable = u
    component = x
  [../]
[]

[Materials]
  [./porosity]
    type = NumbatPorosity
    porosity = 0.2
  [../]
  [./viscosity]
    type = NumbatViscosity
    viscosity = 1e-3
  [../]
  [./permeability]
    type = NumbatPermeability
    permeability = '1e-13 0 0 0 1e-13 0 0 0 1e-13'
  [../]
  [./density]
    type = NumbatDensity
    zero_density = 1000
    delta_density = 10
    concentration = concentration
  [../]
[]

[Kernels]
  [./diffusion]
    type = NumbatDarcy
    variable = pressure
    concentration = concentration
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = pressure
    boundary = left
    value = 2e6
  [../]
  [./right]
    type = DirichletBC
    variable = pressure
    boundary = right
    value = 1e6
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  nl_rel_tol = 1e-12
[]

[VectorPostprocessors]
  [./u]
    type = LineValueSampler
    variable = 'pressure u'
    sort_by = id
    start_point = '0 0 0'
    end_point = '20 0 0'
    num_points = 10
  [../]
[]

[Outputs]
  csv = true
  print_perf_log = true
  file_base = 2Dsteady
  execute_on = timestep_end
[]
