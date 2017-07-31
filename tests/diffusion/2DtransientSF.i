# Tests the NumbatDiffusionSF kernel with a transient executioner

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

[Kernels]
  [./time]
    type = TimeDerivative
    variable = concentration
  [../]
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
  end_time = 5
  dt = 0.5
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
  print_perf_log = true
  file_base = 2DtransientSF
[]
