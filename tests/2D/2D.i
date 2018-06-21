# This input file is used in the documentation. Please do not alter the
# ordering of these blocks

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

[AuxVariables]
  [./u]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./v]
    order = CONSTANT
    family = MONOMIAL
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

[AuxKernels]
  [./uAux]
    type = NumbatDarcyVelocity
    pressure = pressure
    variable = u
    component = x
  [../]
  [./vAux]
    type = NumbatDarcyVelocity
    pressure = pressure
    variable = v
    component = y
  [../]
[]

[BCs]
  [./conctop]
    type = DirichletBC
    variable = concentration
    boundary = top
    value = 1.0
  [../]
  [./Periodic]
    [./x]
      variable = 'concentration pressure'
      auto_direction = x
    [../]
  [../]
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
  file_base = 2D
  print_perf_log = true
[]
