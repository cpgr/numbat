# Tests the NumbatConvectionDG kernel with a transient executioner

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 10
  nx = 100
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

[DGKernels]
  [./convection]
    type = NumbatConvectionDG
    variable = concentration
    pressure = pressure
    gravity = '0 0 0'
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

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  dt = 10
  solve_type = NEWTON
  end_time = 200
[]

[Postprocessors]
  [./mass]
    type = NumbatTotalMass
    variable = concentration
  [../]
[]

[Outputs]
  exodus = true
  print_perf_log = true
  file_base = 2DtransientDG
  execute_on = timestep_end
[]

[BCs]
  [./left]
    type = NeumannBC
    value = 0.001
    variable = concentration
    boundary = left
  [../]
[]
