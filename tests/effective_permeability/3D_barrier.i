# Calculates steady Darcy flux given a prescribed pressure gradient, which
# can be used to calculate the effective permeability

[Mesh]
  type = FileMesh
  file = barrier.msh
  parallel_type = REPLICATED
[]

[Variables]
  [./pressure]
  [../]
  [./concentration]
    initial_condition = 0
  [../]
[]

[AuxVariables]
  [./u]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./v]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./w]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[AuxKernels]
  [./u]
    type = NumbatDarcyVelocity
    variable = u
    pressure = pressure
    gravity = '0 0 0'
  [../]
  [./v]
    type = NumbatDarcyVelocity
    variable = v
    pressure = pressure
    gravity = '0 0 0'
    component = y
  [../]
  [./w]
    type = NumbatDarcyVelocity
    variable = w
    pressure = pressure
    gravity = '0 0 0'
    component = z
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
  [./density]
    type = GenericConstantMaterial
    prop_names = 'density viscosity'
    prop_values = '1 0.1'
  [../]
[]

[Kernels]
  [./darcy]
    type = NumbatDarcy
    variable = pressure
    concentration = concentration
    gravity = '0 0 0'
  [../]
  [./dummy]
    type = Diffusion
    variable = concentration
  [../]
[]

[BCs]
  [./top]
    type = DirichletBC
    variable = pressure
    boundary = top
    value = 1.0
  [../]
  [./bottom]
    type = DirichletBC
    variable = pressure
    boundary = bottom
    value = 2.0
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
  solve_type = NEWTON
  nl_abs_tol = 1e-12
[]

[Postprocessors]
  [./area]
    type = AreaPostprocessor
    boundary = top
  [../]
  [./flux]
    type = SideIntegralVariablePostprocessor
    boundary = top
    variable = w
  [../]
  [./keff]
    type = NumbatEffectivePermeability
    flux = flux
    component = z
    p1 = 2
    p2 = 1
    area = area
  [../]
[]

[Outputs]
  execute_on = TIMESTEP_END
  csv = true
  perf_graph = true
  file_base = 3D_barrier
[]
