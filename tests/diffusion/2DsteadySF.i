# Tests the NumbatDiffusionSF kernel with a steady executioner

[Mesh]
  type = GeneratedMesh
  dim = 2
  ymax = 20
  ny = 10
[]

[Variables]
  [./concentration]
    initial_condition = 0
  [../]
[]

[Kernels]
  [./diffusion]
    type = NumbatDiffusionSF
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
  [./concbottom]
    type = DirichletBC
    variable = concentration
    boundary = bottom
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
  perf_graph = true
  file_base = 2DsteadySF
  execute_on = timestep_end
[]
