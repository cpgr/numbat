# 2D density-driven convective mixing. Instability is seeded by small perturbation
# to porosity. Takes about 5 minutes to run using a single processor.

[Mesh]
  type = NumbatBiasedMesh
  dim = 2
  ymax = 1.5
  nx = 100
  ny = 50
  refined_edge = top
  refined_resolution = 0.001
[]

[Variables]
  [./concentration]
    initial_condition = 0
    scaling = 1e6
  [../]
  [./pressure]
    initial_condition = 1e6
  [../]
[]

[AuxVariables]
  [./noise]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[ICs]
  [./noise]
    type = RandomIC
    variable = noise
    max = 0.003
    min = -0.003
  [../]
[]

[Materials]
  [./porosity]
    type = NumbatPorosity
    porosity = 0.3
    noise = noise
  [../]
  [./permeability]
    type = NumbatPermeability
    permeability = '1e-11 0 0 0 1e-11 0 0 0 1e-11'
  [../]
  [./diffusivity]
    type = NumbatDiffusivity
    diffusivity = 2e-9
  [../]
  [./density]
    type = NumbatDensity
    concentration = concentration
    zero_density = 995
    delta_density = 10.5
    saturated_concentration = 0.049306
  [../]
  [./viscosity]
    type = NumbatViscosity
    viscosity = 6e-4
  [../]
[]

[Kernels]
  [./time]
    type = NumbatTimeDerivative
    variable = concentration
  [../]
  [./diffusion]
    type = NumbatDiffusion
    variable = concentration
  [../]
  [./convection]
    type = NumbatConvection
    variable = concentration
    pressure = pressure
  [../]
  [./darcy]
    type = NumbatDarcy
    variable = pressure
    concentration = concentration
  [../]
[]

[BCs]
  [./conctop]
    type = PresetBC
    variable = concentration
    boundary = top
    value = 0.049306
  [../]
  [./Periodic]
    [./x]
      variable = concentration
      auto_direction = x
    [../]
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
  l_max_its = 200
  end_time = 3e5
  solve_type = NEWTON
  petsc_options = -ksp_snes_ew
  petsc_options_iname = '-pc_type -sub_pc_type -ksp_atol'
  petsc_options_value = 'bjacobi ilu 1e-12'
  nl_abs_tol = 1e-10
  nl_max_its = 25
  dtmax = 2e3
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 1
  [../]
[]

[Postprocessors]
  [./boundaryfluxint]
    type = NumbatSideFlux
    variable = concentration
    boundary = top
  [../]
  [./mass]
    type = NumbatTotalMass
    variable = concentration
  [../]
[]

[Outputs]
  perf_graph = true
  [./exodus]
    type = Exodus
    file_base = 2Dddc
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  [./csvoutput]
    type = CSV
    file_base = 2Dddc
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
