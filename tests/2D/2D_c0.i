# Dimensional test with specified saturated concentration

[Mesh]
  type = GeneratedMesh
  dim = 2
  ny = 50
[]

[Variables]
  [./concentration]
    initial_condition = 0
  [../]
  [./pressure]
    initial_condition = 1e6
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

[Kernels]
  [./time]
    type = NumbatTimeDerivative
    variable = concentration
  [../]
  [./diffusion]
    type = NumbatDiffusion
    variable = concentration
  [../]
  [./convection]
    type = NumbatConvection
    variable = concentration
    pressure = pressure
  [../]
  [./darcy]
    type = NumbatDarcy
    variable = pressure
    concentration = concentration
  [../]
[]

[BCs]
  [./conctop]
    type = DirichletBC
    variable = concentration
    boundary = top
    value = 0.05
  [../]
  [./Periodic]
    [./x]
      variable = 'concentration pressure'
      auto_direction = x
    [../]
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
  end_time = 50
  solve_type = NEWTON
  petsc_options_iname = '-ksp_type -pc_type -pc_sub_type'
  petsc_options_value = 'gmres hypre lu'
[]

[Postprocessors]
  [./boundary_flux]
    type = NumbatSideFlux
    variable = concentration
    boundary = top
  [../]
  [./total_mass]
    type = NumbatTotalMass
    variable = concentration
  [../]
[]

[Outputs]
  execute_on = TIMESTEP_END
  csv = true
  file_base = 2D_c0
[]
