# Tests the NumbatDarcy kernel with a steady executioner
[Mesh]
  type = GeneratedMesh
  dim = 3
  xmax = 10
  ymax = 10
  zmax = 20
  nx = 1
  ny = 1
  nz = 10
[]

[Variables]
  [./pressure]
  [../]
[]

[AuxVariables]
  [./concentration]
    initial_condition = 0.1
  [../]
  [./w]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[AuxKernels]
  [./w]
    type = NumbatDarcyVelocity
    pressure = pressure
    variable = w
    component = z
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
  [./top]
    type = DirichletBC
    variable = pressure
    boundary = front
    value = 2e6
  [../]
  [./bottom]
    type = DirichletBC
    variable = pressure
    boundary = back
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
  [./w]
    type = LineValueSampler
    variable = 'pressure w'
    sort_by = id
    start_point = '0 0 0'
    end_point = '0 0 20'
    num_points = 10
  [../]
[]

[Outputs]
  csv = true
  print_perf_log = true
  file_base = 3Dsteady_gravity
  execute_on = timestep_end
[]
