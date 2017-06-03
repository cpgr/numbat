# Tests the NumbatConvection kernel with a transient executioner

[Mesh]
  type = GeneratedMesh
  dim = 3
  zmax = 10
  nz = 50
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
    function = (10+z)*1e5
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
  [../]
  [./time]
    type = NumbatTimeDerivative
    variable = concentration
  [../]
[]

[BCs]
  [./conctop]
    type = DirichletBC
    variable = concentration
    boundary = front
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
  file_base = 3Dtransient
  execute_on = timestep_end
[]
