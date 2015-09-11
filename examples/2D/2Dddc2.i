# Density-driven convective mixing with permeability anisotropy
# Example with gamma = kv/kh = 0.5
# To implement anisotropy, must change the gamma and coeff_tensor parameters in the kernels

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 1000
  ymin = -200
  ymax = 0
  nx = 80
  ny = 20
  nz = 0
[]

[MeshModifiers]
  [./verticalrefinement]
    type = VerticalRefine
    mesh_top = 0
    mesh_bottom = -200
  [../]
[]

[Adaptivity]
  marker = combomarker
  max_h_level = 2
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
      coarsen = 0.0025
      refine = 0.005
      indicator = gradjumpindicator
    [../]
    [./boxmarker]
      type = BoxMarker
      bottom_left = '0 -1.0 0'
      top_right = '1000 0 0'
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
    [./InitialCondition]
      type = PerturbationIC
      variable = concentration
      amplitude = 0.01
      seed = 1
    [../]
  [../]
  [./streamfunction]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0.0
  [../]
[]

[Kernels]
  [./TwoDDarcyDDC]
    type = DarcyDDC
    variable = streamfunction
    concentration_variable = concentration
    gamma = 0.5
  [../]
  [./TwoDConvectionDiffusionDDC]
    type = ConvectionDiffusionDDC
    variable = concentration
    streamfunction_variable = streamfunction
    coeff_tensor = '0.5 0 0 0 1 0 0 0 1'
  [../]
  [./TimeDerivative]
    type = TimeDerivative
    variable = concentration
  [../]
[]

[BCs]
  active = 'Periodic streamfuntop conctop streamfunbottom'
  [./conctop]
    type = DirichletBC
    variable = concentration
    boundary = top
    value = 1.0
  [../]
  [./streamfuntop]
    type = DirichletBC
    variable = streamfunction
    boundary = top
    value = 0.0
  [../]
  [./streamfunbottom]
    type = DirichletBC
    variable = streamfunction
    boundary = bottom
    value = 0.0
  [../]
  [./Periodic]
    [./x]
      variable = 'concentration streamfunction'
      auto_direction = x
    [../]
  [../]
[]

[Executioner]
  type = Transient
  scheme = bdf2
  dtmin = 0.1
  dtmax = 200
  end_time = 5000
  solve_type = PJFNK
  petsc_options_iname = '-ksp_type -pc_type -pc_sub_type'
  petsc_options_value = 'gmres asm lu'
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 1
    cutback_factor = 0.5
    growth_factor = 2
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
    boundary = top
    diffusivity = tmpdiff
  [../]
  [./numdofs]
    type = NumDOFs
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Outputs]
  active = 'exodus console csv'
  [./console]
    type = Console
    perf_log = true
    output_nonlinear = true
  [../]
  [./exodus]
    type = Exodus
    file_base = 2Dddc2
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  [./csvoutput]
    type = CSV
    file_base = 2Dddc2
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
