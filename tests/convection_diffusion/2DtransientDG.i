# Convection-diffusion problem. The pressure gradient and material properties are
# set up so that the fluid velocity is 0.001 m/s.

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 20
  nx = 50
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
    function = (30-x)*1e5
  [../]
[]

[Materials]
  [./porosity]
    type = NumbatPorosity
    porosity = 0.1
  [../]
  [./permeability]
    type = NumbatPermeability
    permeability = '1e-11 0 0 0 1e-11 0 0 0 1e-11'
  [../]
  [./viscosity]
    type = NumbatViscosity
    viscosity = 5e-4
  [../]
  [./density]
    type = NumbatDensity
    zero_density = 1000
    delta_density = 0
    concentration = concentration
  [../]
  [./diffusivity]
    type = NumbatDiffusivity
    diffusivity = 5e-4
  [../]
[]

[DGKernels]
  [./convection]
    type = NumbatConvectionDG
    variable = concentration
    pressure = pressure
    gravity = '0 0 0'
  [../]
  [./diffusion]
    type = NumbatDiffusionDG
    variable = concentration
    epsilon = -1
    sigma = 6
  [../]
[]

[Kernels]
  [./convection]
    type = NumbatConvection
    variable = concentration
    pressure = pressure
    gravity = '0 0 0'
  [../]
  [./diffusion]
    type = NumbatDiffusion
    variable = concentration
  [../]
  [./time]
    type = NumbatTimeDerivative
    variable = concentration
  [../]
[]

[BCs]
  [./concleft]
    type = NumbatDiffusionDGBC
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
  dt = 2
  solve_type = NEWTON
  end_time = 500
[]

[VectorPostprocessors]
  [./conc]
    type = LineValueSampler
    variable = concentration
    sort_by = id
    start_point = '0 0 0'
    end_point = '20 0 0'
    num_points = 50
  [../]
[]

[Outputs]
  csv = true
  perf_graph = true
  file_base = 2DtransientDG
  execute_on = final
[]
