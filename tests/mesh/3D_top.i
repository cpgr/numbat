[Mesh]
  type = NumbatBiasedMesh
  dim = 3
  nz = 10
  zmax = 10
  refined_edge = front
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
  [./concfront]
    type = DirichletBC
    variable = concentration
    boundary = front
    value = 1.0
  [../]
  [./concback]
    type = DirichletBC
    variable = concentration
    boundary = back
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
  nl_rel_tol = 1e-12
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
  file_base = 3D_top
[]
