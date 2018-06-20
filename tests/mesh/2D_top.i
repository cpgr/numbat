[Mesh]
  type = NumbatBiasedMesh
  dim = 2
  ny = 10
  ymax = 10
  refined_edge = top
  refined_resolution = 0.1
[]

[Variables]
  [./concentration]
    initial_condition = 0
  [../]
[]

[Kernels]
  [./diffusion]
    type = Diffusion
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
  type = Transient
  end_time = 1
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
  execute_on = TIMESTEP_END
  csv = true
  file_base = 2D_top
[]
