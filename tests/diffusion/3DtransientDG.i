# Tests the NumbatDiffusionDG kernel with a transient executioner

[Mesh]
  type = GeneratedMesh
  dim = 3
  zmax = 20
  nz = 20
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
    porosity = 0.1
  [../]
  [./diffusivity]
    type = NumbatDiffusivity
    diffusivity = 0.5
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
[]

[DGKernels]
  [./diffusion]
    type = NumbatDiffusionDG
    variable = concentration
    epsilon = -1
    sigma = 6
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
  type = Transient
  solve_type = NEWTON
  end_time = 10
  dt = 1
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
  execute_on = final
  csv = true
  perf_graph = true
  file_base = 3DtransientDG
[]
