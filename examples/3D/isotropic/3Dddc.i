# 3D density-driven convective mixing. Instability is seeded by small perturbation
# to porosity. Don't try this on a laptop!

[Mesh]
  type = NumbatBiasedMesh
  dim = 3
  zmax = 1.5
  nx = 20
  ny = 20
  nz = 500
  refined_edge = front
  refined_resolution = 0.001
[]

[Numbat]
  [./Dimensional]
    concentration_scaling = 1e6
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
  [../]
  [./pressure]
    type = ConstantIC
    variable = pressure
    value = 1e6
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
  petsc_options_iname = '-pc_type -sub_pc_type -ksp_atol -pc_asm_overlap'
  petsc_options_value = 'asm ilu 1e-12 4'
  nl_abs_tol = 1e-10
  nl_max_its = 25
  dtmax = 2e3
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 1
  [../]
[]

[Outputs]
  perf_graph = true
  [./exodus]
    type = Exodus
    file_base = 3Dddc
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  [./csvoutput]
    type = CSV
    file_base = 3Dddc
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
