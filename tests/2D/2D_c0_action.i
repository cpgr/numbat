[Mesh]
  type = GeneratedMesh
  dim = 2
  ny = 50
[]

[Numbat]
  [./Dimensional]
    boundary_concentration = 0.05
  [../]
[]

[ICs]
  [./concentration]
    type = ConstantIC
    variable = concentration
    value = 0
  [../]
  [./pressure]
    type = ConstantIC
    variable = pressure
    value = 1e6
  [../]
[]

[Materials]
  [./porosity]
    type = NumbatPorosity
    porosity = 0.2
  [../]
  [./permeability]
    type = NumbatPermeability
    permeability = '1e-12 0 0 0 1e-12 0 0 0 1e-12'
  [../]
  [./diffusivity]
    type = NumbatDiffusivity
    diffusivity = 1e-3
  [../]
  [./density]
    type = NumbatDensity
    concentration = concentration
    zero_density = 1000
    delta_density = 10
    saturated_concentration = 0.05
  [../]
  [./viscosity]
    type = NumbatViscosity
    viscosity = 1e-3
  [../]
[]

[Executioner]
  type = Transient
  end_time = 50
  solve_type = NEWTON
  petsc_options_iname = '-ksp_type -pc_type -pc_sub_type'
  petsc_options_value = 'gmres hypre lu'
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Outputs]
  execute_on = TIMESTEP_END
  csv = true
  file_base = 2D_c0
  perf_graph = true
[]
