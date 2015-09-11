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

[Variables]
  [./concentration]
    order = FIRST
    family = LAGRANGE
  [../]
  [./streamfunctionx]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0.0
  [../]
  [./streamfunctiony]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0.0
  [../]
[]

[Kernels]
  [./ThreeDDarcyDDCx]
    type = DarcyDDC
    variable = streamfunctionx
    concentration_variable = concentration
    component = x
    gamma = 0.5
  [../]
  [./ThreeDDarcyDDCy]
    type = DarcyDDC
    variable = streamfunctiony
    concentration_variable = concentration
    component = y
    gamma = 0.5
  [../]
  [./ThreeDConvectionDiffusionDDC]
    type = ConvectionDiffusionDDC
    variable = concentration
    streamfunction_variable = 'streamfunctionx streamfunctiony'
    coeff_tensor = '0.5 0 0 0 0.5 0 0 0 1'
  [../]
  [./TimeDerivative]
    type = TimeDerivative
    variable = concentration
  [../]
[]

[BCs]
  [./conctop]
    type = DirichletBC
    variable = concentration
    boundary = front
    value = 1.0
  [../]
  [./streamfunxtop]
    type = DirichletBC
    variable = streamfunctionx
    boundary = front
    value = 0.0
  [../]
  [./streamfunxbottom]
    type = DirichletBC
    variable = streamfunctionx
    boundary = back
    value = 0.0
  [../]
  [./streamfunytop]
    type = DirichletBC
    variable = streamfunctiony
    boundary = front
    value = 0.0
  [../]
  [./streamfunybottom]
    type = DirichletBC
    variable = streamfunctiony
    boundary = back
    value = 0.0
  [../]
  [./Periodic]
    [./xy]
      variable = 'concentration streamfunctionx streamfunctiony'
      auto_direction = 'x y'
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
  scheme = bdf2
  dtmin = 0.1
  dtmax = 1000
  end_time = 3000
  solve_type = PJFNK
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 1
  [../]
[]

[Materials]
  [./tmpmat]
    type = GenericConstantMaterial
    block = 0
    prop_names = tmpdiff
    prop_values = 1.0
  [../]
[]

[Postprocessors]
  [./boundaryfluxint]
    type = SideFluxIntegral
    variable = concentration
    boundary = front
    diffusivity = tmpdiff
  [../]
  [./numdofs]
    type = NumDOFs
  [../]
[]

[Outputs]
  output_initial = true
  [./console]
    type = Console
    perf_log = true
    output_nonlinear = true
    output_linear = true
  [../]
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

