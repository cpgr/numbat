# Density-driven convective mixing with permeability anisotropy
# Example with gamma = kv/kh = 0.5
# To implement anisotropy, must change the gamma and coeff_tensor parameters in the kernels

[Mesh]
  type = GeneratedMesh
  dim = 3
  xmax = 200
  ymax = 200
  zmin = -200
  zmax = 0
  nx = 10
  ny = 10
  nz = 10
[]

[Adaptivity]
  max_h_level = 2
  initial_marker = boxmarker
  initial_steps = 1
  marker = combomarker
  [./Indicators]
    [./gradjumpindicator]
      type = GradientJumpIndicator
      variable = concentration
    [../]
  [../]
  [./Markers]
    [./errormarker]
      type = ErrorToleranceMarker
      coarsen = 2.5
      refine = 1
      indicator = gradjumpindicator
    [../]
    [./boxmarker]
      type = BoxMarker
      bottom_left = '0 0 -10'
      top_right = '1000 1000 0'
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
    gamma = 0.5
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
  scheme = bdf2
  dtmin = 0.1
  dtmax = 1000
  end_time = 3000
  solve_type = NEWTON
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 1
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
    file_base = 3Dddc2
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  [./csvoutput]
    type = CSV
    file_base = 3Dddc2
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
