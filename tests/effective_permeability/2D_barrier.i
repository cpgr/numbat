# Calculates steady Darcy flux given a prescribed pressure gradient, which
# can be used to calculate the effective permeability
#
# This test has a flow barrier in the middle

[Mesh]
  [./generate]
    type = GeneratedMeshGenerator
    dim = 2
    xmax = 1.1
    ymax = 1.1
    nx = 11
    ny = 11
  [../]
  [./barrier]
    type = SubdomainBoundingBoxGenerator
    input = generate
    bottom_left = '0.5 0.3 0'
    top_right = '0.6 0.8 0'
    block_id = 1
  [../]
  [./deleter]
    type = BlockDeletionGenerator
    input = barrier
    block_id = 1
  [../]
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
[]

[Functions]
  [./pic]
    type = ParsedFunction
    value = '2-x/2'
  [../]
[]

[ICs]
  [./pressure]
    type = FunctionIC
    variable = pressure
    function = pic
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
  [./left]
    type = DirichletBC
    variable = pressure
    boundary = left
    value = 2.0
  [../]
  [./right]
    type = DirichletBC
    variable = pressure
    boundary = right
    value = 1.0
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
    boundary = right
  [../]
  [./flux]
    type = SideIntegralVariablePostprocessor
    boundary = right
    variable = u
  [../]
  [./keff]
    type = NumbatEffectivePermeability
    flux = flux
    component = x
    p1 = 2
    p2 = 1
    area = area
  [../]
[]

[Outputs]
  execute_on = TIMESTEP_END
  csv = true
  file_base = 2D_barrier
  perf_graph = true
[]
