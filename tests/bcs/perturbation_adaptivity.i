# Tests NumbatPerturbationBC with adaptivity to ensure that the fluctuation is
# correctly applied

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 50
  nx = 10
  ny = 2
[]

[Adaptivity]
  max_h_level = 2
  marker = uniform
  [./Markers]
    [./uniform]
      type = UniformMarker
      mark = REFINE
    [../]
  [../]
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
  type = Transient
  solve_type = NEWTON
  end_time = 3
  dt = 1
  nl_abs_tol = 1e-12
[]

[Outputs]
  exodus = true
  print_perf_log = true
  file_base = perturbation_adaptivity
  execute_on = final
[]
