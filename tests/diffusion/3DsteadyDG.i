# Tests the NumbatDiffusionDG kernel with a steady executioner

[Mesh]
  type = GeneratedMesh
  dim = 3
  xmax = 10
  ymax = 10
  zmax = 20
  nx = 2
  ny = 2
  nz = 10
[]

[Variables]
  [./concentration]
    initial_condition = 0
    order = FIRST
    family = MONOMIAL
  [../]
[]

[Materials]
  [./porosity]
    type = NumbatPorosity
    porosity = 0.2
  [../]
  [./diffusivity]
    type = NumbatDiffusivity
    diffusivity = 1e-6
  [../]
[]

[DGKernels]
  [./diffusion]
    type = NumbatDiffusionDG
    variable = concentration
    epsilon = -1
    sigma = 6
  [../]
[]

[Kernels]
  [./diffusion]
    type = NumbatDiffusion
    variable = concentration
  [../]
[]

[BCs]
  [./conctop]
    type = NumbatDiffusionDGBC
    variable = concentration
    boundary = front
    epsilon = -1.0
    sigma = 6
    value = 1
  [../]
  [./concbottom]
    type = NumbatDiffusionDGBC
    variable = concentration
    boundary = back
    epsilon = -1.0
    sigma = 6
    value = 0
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  nl_abs_tol = 1e-8
[]

[VectorPostprocessors]
  [./conc]
    type = LineValueSampler
    variable = concentration
    sort_by = id
    start_point = '0 0 0'
    end_point = '0 0 20'
    num_points = 20
  [../]
[]

[Outputs]
  csv = true
  print_perf_log = true
  print_linear_residuals = false
  file_base = 3DsteadyDG
  execute_on = timestep_end
[]
