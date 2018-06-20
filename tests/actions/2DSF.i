[Mesh]
  type = GeneratedMesh
  dim = 2
  ymin = -100
  ymax = 0
  ny = 20
[]

[Numbat]
  [Dimensionless]
    dim = 2
  [../]
[]

[Executioner]
  type = Transient
  end_time = 1
  solve_type = PJFNK
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]
