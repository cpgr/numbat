# Density-driven convective mixing with permeability anisotropy using the
# streamfunction formulation in 2D.
# Example with gamma = kv/kh = 0.75
# Density-driven convective mixing
# The dimensionless Numbat action is used to add all variables, kernels etc.
# Mesh adaptivity used to refine mesh wround fingers
# A coarse grid and time stepping used to allow this model to run in ~ 2 minutes

[Mesh]
  type = NumbatBiasedMesh
  dim = 2
  xmax = 1000
  ymin = -500
  ymax = 0
  nx = 100
  ny = 25
  refined_edge = top
  refined_resolution = 10
[]

[Numbat]
  [./Dimensionless]
    gamma = 0.75
    periodic_bcs = true
  [../]
[]

[Adaptivity]
  marker = errormarker
  max_h_level = 1
  [./Indicators]
    [./gradjumpindicator]
      type = GradientJumpIndicator
      variable = concentration
    [../]
  [../]
  [./Markers]
    [./errormarker]
      type = ErrorFractionMarker
      refine = 0.25
      indicator = gradjumpindicator
    [../]
  [../]
[]

[ICs]
  [./concentration]
    type = NumbatPerturbationIC
    variable = concentration
    amplitude = 0.1
    seed = 1
  [../]
[]

[Executioner]
  type = Transient
  dtmax = 100
  end_time = 3000
  start_time = 1
  solve_type = NEWTON
  nl_abs_tol = 1e-10
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 1
    cutback_factor = 0.5
    growth_factor = 2
  [../]
[]

[Postprocessors]
  [./numdofs]
    type = NumDOFs
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
    petsc_options = -snes_ksp_ew
    petsc_options_iname = '-pc_type -sub_pc_type -ksp_atol'
    petsc_options_value = 'asm ilu 1e-12'
  [../]
[]

[Outputs]
  perf_graph = true
  [./exodus]
    type = Exodus
    file_base = 2DddcSF
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  [./csvoutput]
    type = CSV
    file_base = 2DddcSF
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
