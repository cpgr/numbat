# Tests NumbatPerturbationBC

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 100
  nx = 20
  ny = 2
[]

[Variables]
  [./concentration]
    initial_condition = 0
  [../]
[]

[AuxVariables]
  [./noise]
  [../]
[]

[ICs]
  [./noise]
    type = RandomIC
    variable = noise
    min = 0
    max = 0.05
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
    boundary = top
    variable = concentration
    value = 1
    noise = noise
  [../]
  [./Periodic]
    [./x]
      auto_direction = x
      variable = concentration
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
  type = Steady
  solve_type = NEWTON
[]

[Outputs]
  exodus = true
  perf_graph = true
  file_base = perturbation
  execute_on = timestep_end
[]
