# Tests the NumbatDiffusion kernel with a transient executioner

[Mesh]
  type = GeneratedMesh
  dim = 2
  ymax = 20
  ny = 20
[]

[Variables]
  [./concentration]
    initial_condition = 0
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

[BCs]
  [./conctop]
    type = DirichletBC
    variable = concentration
    boundary = top
    value = 1.0
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
    type = NodalValueSampler
    variable = concentration
    sort_by = id
  [../]
[]

[Outputs]
  execute_on = final
  csv = true
  perf_graph = true
  file_base = 2Dtransient
[]
