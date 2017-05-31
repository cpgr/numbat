# Tests NumbatPerturbationBC

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 100
  nx = 100
  ny = 1
[]

[Variables]
  [./concentration]
    initial_condition = 0
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

[Kernels]
  [./diffusion]
    type = NumbatDiffusion
    variable = concentration
  [../]
[]

[BCs]
  [./top]
    type = NumbatPerturbationBC
    variable = concentration
    boundary = top
    value = 1.0
    amplitude = 0.05
    seed = 1
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
[]

[VectorPostprocessors]
  [./conc]
    type = NodalValueSampler
    variable = concentration
    sort_by = id
  [../]
[]

[Outputs]
  csv = true
  print_perf_log = true
  file_base = perturbation
  execute_on = timestep_end
[]
