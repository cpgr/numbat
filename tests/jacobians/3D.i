[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 2
  ny = 3
  nz = 4
[]

[Variables]
  [./concentration]
  [../]
  [./pressure]
  [../]
[]

[Materials]
  [./porosity]
    type = NumbatPorosity
    porosity = 0.2
  [../]
  [./permeability]
    type = NumbatPermeability
    permeability = '1 0 0 0 1 0 0 0 1'
  [../]
  [./diffusivity]
    type = NumbatDiffusivity
    diffusivity = 1e-2
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

[Kernels]
  [./darcy]
    type = NumbatDarcy
    variable = pressure
    concentration = concentration
  [../]
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
[]

[BCs]
  [./conctop]
    type = DirichletBC
    variable = concentration
    boundary = top
    value = 1.0
  [../]
[]

[ICs]
  [./concentrationIC]
    type = RandomIC
    min = 0
    max = 1
    variable = concentration
  [../]
  [./pressureIC]
    type = RandomIC
    min = 1e6
    max = 2e6
    variable = pressure
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
  dtmin = 1
  end_time = 1
  solve_type = NEWTON
[]
