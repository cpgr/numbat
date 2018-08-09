[Mesh]
  type = GeneratedMesh
  dim = 2
  ymin = -100
  ymax = 0
  ny = 20
  nz = 0
  bias_y = 0.75
[]

[Numbat]
  [./Dimensionless]
    gamma = 0.75
  [../]
[]

[Executioner]
  type = Transient
  end_time = 500
  dt = 10
  solve_type = PJFNK
  petsc_options_iname = '-ksp_type -pc_type -pc_sub_type'
  petsc_options_value = 'gmres asm lu'
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Outputs]
  perf_graph = true
  [./csvoutput]
    type = CSV
    file_base = 2DSF_anisotropic
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
