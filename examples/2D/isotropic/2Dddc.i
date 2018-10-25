# 2D density-driven convective mixing
# The dimensional Numbat action is used to add all variables, kernels etc.
# Instability is seeded by small perturbation to porosity.
# A coarse grid and time stepping used to allow this model to run in ~ 15 minutes

[Mesh]
  type = NumbatBiasedMesh
  dim = 2
  nx = 150
  ny = 50
  ymax = 0.5
  refined_edge = top
  refined_resolution = 0.001
[]

[Numbat]
  [./Dimensional]
    concentration_scaling = 1e4
    boundary_concentration = 0.049306
    periodic_bcs = true
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
    legacy_generator = true
  [../]
  [./pressure]
    type = ConstantIC
    variable = pressure
    value = 10e6
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
    zero_density = 994.56
    delta_density = 10.45
    saturated_concentration = 0.049306
  [../]
  [./viscosity]
    type = NumbatViscosity
    viscosity = 0.5947e-3
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Functions]
  [./timesteps]
    type = PiecewiseConstant
    x = '0 100 500 1e3 1e4 2e5'
    y = '10 50 100 500 1e3 1e3'
  [../]
[]

[Executioner]
  type = Transient
  l_max_its = 100
  end_time = 2e5
  solve_type = NEWTON
  petsc_options = -ksp_snes_ew
  petsc_options_iname = '-pc_type -sub_pc_type -ksp_atol'
  petsc_options_value = 'asm ilu 1e-12'
  nl_abs_tol = 1e-8
  [./TimeStepper]
    type = FunctionDT
    function = timesteps
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
