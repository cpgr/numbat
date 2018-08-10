# Density-driven convective mixing in a 3D representation of a 2D model. Only a single element is
# used in the y direction.
#
# Note: This example may take some time to run. At least 8 processors are recommended.

[Mesh]
  type = NumbatBiasedMesh
  dim = 3
  xmax = 1000
  zmin = -200
  zmax = 0
  nx = 80
  nz = 20
  ymax = 1
  ny = 1
  refined_edge = top
  refined_resolution = 2
[]

[Adaptivity]
  marker = combomarker
  max_h_level = 1
  initial_marker = boxmarker
  initial_steps = 1
  [./Indicators]
    [./gradjumpindicator]
      type = GradientJumpIndicator
      variable = concentration
    [../]
  [../]
  [./Markers]
    [./errormarker]
      type = ErrorToleranceMarker
      refine = 0.005
      indicator = gradjumpindicator
    [../]
    [./boxmarker]
      type = BoxMarker
      bottom_left = '0 0.0 -1.0'
      top_right = '1000 1 0'
      inside = refine
      outside = dont_mark
    [../]
    [./combomarker]
      type = ComboMarker
      markers = 'boxmarker errormarker'
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
    file_base = 3Dddcp
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  [./csvoutput]
    type = CSV
    file_base = 3Dddcp
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
