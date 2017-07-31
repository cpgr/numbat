# Tests the NumbatConvection kernel with a transient executioner. The pressure gradient
# and material properties are set up so that the fluid velocity is 0.001 m/s.
# This test is a heavier version of 3Dtransient.i, and uses smaller time steps to reduce
# numberical diffusion. It is not run as part of the automatic test suite, but can be
# run using the --heavy flag.

[Mesh]
  type = GeneratedMesh
  dim = 3
  zmax = 1
  nz = 200
[]

[Variables]
  [./concentration]
    initial_condition = 0
  [../]
[]

[AuxVariables]
  [./pressure]
  [../]
  [./w]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./w]
    type = NumbatDarcyVelocity
    variable = w
    pressure = pressure
    component = z
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
  print_perf_log = true
  file_base = 3Dtransient_heavy
  execute_on = final
[]
