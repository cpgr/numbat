# Tests the NumbatConvection kernel with a transient executioner. The pressure gradient
# and material properties are set up so that the fluid velocity is 0.001 m/s.
# This test is a heavier version of 2Dtransient.i, and uses smaller time steps to reduce
# numberical diffusion. It is not run as part of the automatic test suite, but can be
# run using the --heavy flag.

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 1
  nx = 200
[]

[Variables]
  [./concentration]
    initial_condition = 0
  [../]
[]

[AuxVariables]
  [./pressure]
  [../]
  [./u]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./u]
    type = NumbatDarcyVelocity
    variable = u
    pressure = pressure
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
    delta_density = 0
    concentration = concentration
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
  dt = 0.1
  solve_type = NEWTON
  end_time = 100
  timestep_tolerance = 1e-10
[]

[VectorPostprocessors]
  [./conc]
    type = NodalValueSampler
    variable = concentration
    sort_by = id
  [../]
[]

[Outputs]
  csv = true
  perf_graph = true
  file_base = 2Dtransient_heavy
  execute_on = final
[]
