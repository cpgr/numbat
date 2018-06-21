[Mesh]
  type = GeneratedMesh
  dim = 2
[]

[Numbat]
  [./Dimensional]
  [../]
[]

[ICs]
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
  [../]
  [./viscosity]
    type = NumbatViscosity
    viscosity = 1e-3
  [../]
[]

[Executioner]
  type = Transient
  end_time = 1
  solve_type = PJFNK
  petsc_options_iname = '-ksp_type -pc_type -pc_sub_type'
  petsc_options_value = 'gmres hypre ilu'
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]
