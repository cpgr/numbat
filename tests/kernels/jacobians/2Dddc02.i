[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 3
  ny = 3
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
  [./diffusivity]
    type = NumbatDiffusivity
    diffusivity = 1e-9
  [../]
  [./density]
    type = NumbatDensity
    concentration = concentration
    zero_density = 1000
    delta_density = 10
    equilibrium_concentration = 0.025
  [../]
[]

[Kernels]
  [./darcy]
    type = NumbatDarcy
    variable = pressure
    concentration = concentration
    gravity = '0 -10 0'
    permeability = '1 0 0 0 1 0 0 0 1'
    viscosity = 1e-3
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
    viscosity = 1e-3
    gravity = '0 -10 0'
    permeability = '1 0 0 0 1 0 0 0 1'
    pressure = pressure
  [../]
[]

[BCs]
  [./conctop]
    type = PresetBC
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
