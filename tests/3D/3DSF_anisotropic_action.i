[Mesh]
  type = NumbatBiasedMesh
  dim = 3
  xmax = 10
  ymax = 10
  zmin = -100
  zmax = 0
  nx = 1
  ny = 1
  nz = 10
  refined_edge = top
  refined_resolution = 1
[]

[Numbat]
  [./Dimensionless]
    gamma = 0.5
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
  end_time = 500
  dt = 10
  solve_type = PJFNK
[]

[Outputs]
  [./console]
    type = Console
    perf_log = true
    output_nonlinear = true
    output_linear = true
  [../]
  [./csvoutput]
    type = CSV
    file_base = 3DSF_anisotropic
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]
