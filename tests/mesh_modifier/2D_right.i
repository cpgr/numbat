[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  xmax = 10
[]

[MeshModifiers]
  [./bias]
    type = NumbatBiasedMesh
    refined_edge = right
    refined_resolution = 0.1
    num_elems = 10
  [../]
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
  [./concleft]
    type = DirichletBC
    variable = concentration
    boundary = left
    value = 0.0
  [../]
  [./concright]
    type = DirichletBC
    variable = concentration
    boundary = right
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
  type = Steady
  nl_rel_tol = 1e-12
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
  file_base = 2D_right
[]
