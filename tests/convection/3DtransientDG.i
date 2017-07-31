# Tests the NumbatConvectionDG kernel with a transient executioner

[Mesh]
  type = GeneratedMesh
  dim = 3
  zmax = 1
  nz = 50
[]

[Variables]
  [./concentration]
    family = MONOMIAL
    order = FIRST
  [../]
[]

[AuxVariables]
  [./pressure]
  [../]
[]

[ICs]
  [./pressure]
    type = FunctionIC
    variable = pressure
    function = (20+z)*1e5
  [../]
[]

[Materials]
  [./porosity]
    type = NumbatPorosity
    porosity = 0.2
  [../]
  [./permeability]
    type = NumbatPermeability
    permeability = '1e-11 0 0 0 1e-11 0 0 0 1e-11'
  [../]
  [./viscosity]
    type = NumbatViscosity
    viscosity = 1e-3
  [../]
  [./density]
    type = NumbatDensity
    zero_density = 1000
    delta_density = 0
    concentration = concentration
  [../]
[]

[DGKernels]
  [./convection]
    type = NumbatConvectionDG
    variable = concentration
    pressure = pressure
    gravity = '0 0 0'
  [../]
[]

[Kernels]
  [./convection]
    type = NumbatConvection
    variable = concentration
    pressure = pressure
    gravity = '0 0 0'
  [../]
  [./time]
    type = NumbatTimeDerivative
    variable = concentration
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
  dt = 2
  solve_type = NEWTON
  end_time = 100
[]

[VectorPostprocessors]
  [./conc]
    type = LineValueSampler
    variable = concentration
    sort_by = id
    start_point = '0 0 0'
    end_point = '0 0 1'
    num_points = 50
  [../]
[]

[Outputs]
  csv = true
  print_perf_log = true
  file_base = 3DtransientDG
  execute_on = final
[]

[BCs]
  [./top]
    type = NeumannBC
    value = 0.001
    variable = concentration
    boundary = front
  [../]
[]
