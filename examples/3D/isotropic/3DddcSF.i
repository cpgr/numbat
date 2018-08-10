# Density-driven convective mixing in a 3D model using the streamfunction
# formulation.
#
# Note: do not run this on a laptop!

[Mesh]
  type = NumbatBiasedMesh
  dim = 3
  xmax = 500
  ymax = 500
  zmin = -200
  zmax = 0
  nx = 40
  ny = 40
  nz = 20
  refined_edge = top
  refined_resolution = 2
[]

[Adaptivity]
  max_h_level = 1
  initial_marker = boxmarker
  initial_steps = 1
  marker = errormarker
  [./Indicators]
    [./gradjumpindicator]
      type = GradientJumpIndicator
      variable = concentration
    [../]
  [../]
  [./Markers]
    [./errormarker]
      type = ErrorToleranceMarker
      refine = 0.05
      indicator = gradjumpindicator
    [../]
    [./boxmarker]
      type = BoxMarker
      bottom_left = '0 0 -10'
      top_right = '500 500 0'
      inside = refine
      outside = dont_mark
    [../]
  [../]
[]

[Numbat]
  [./Dimensionless]
  [../]
[]

[ICs]
  [./concentration]
    type = NumbatPerturbationIC
    variable = concentration
    amplitude = 0.1
    seed = 1
  [../]
  [./streamfunctionx]
    type = ConstantIC
    variable = streamfunction_x
    value = 0.0
  [../]
  [./streamfunctiony]
    type = ConstantIC
    variable = streamfunction_y
    value = 0.0
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
  dtmax = 100
  end_time = 2500
  start_time = 1
  solve_type = NEWTON
  petsc_options = -snes_ksp_ew
  petsc_options_iname = '-pc_type -sub_pc_type -ksp_atol -pc_asm_overlap'
  petsc_options_value = 'asm ilu 1e-12 4'
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

[Outputs]
  perf_graph = true
  [./exodus]
    type = Exodus
    file_base = 3DddcSF
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  [./csvoutput]
    type = CSV
    file_base = 3DddcSF
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
