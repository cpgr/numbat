# Tests the NumbatConvection kernel with a transient executioner

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 10
  nx = 50
[]

[Variables]
  [./concentration]
    initial_condition = 0
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
    function = (20-x)*1e5
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
    delta_density = 10
    concentration = concentration
  [../]
[]

[Kernels]
  [./convcection]
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

[BCs]
  [./concleft]
    type = DirichletBC
    variable = concentration
    boundary = left
    value = 1
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
  dt = 50
  solve_type = NEWTON
  end_time = 500
[]

[Outputs]
  exodus = true
  print_perf_log = true
  file_base = 2Dtransient
  execute_on = timestep_end
[]
