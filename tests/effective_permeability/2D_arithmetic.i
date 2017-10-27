# Calculates steady Darcy flux given a prescribed pressure gradient, which
# can be used to calculate the effective permeability
#
# This test has two homogeneous layers, so the effective permeability should
# be equal to the arithmetic mean of the permeabilities
# keff = (1 + 10)/2 = 5.5

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 2
  ymax = 2
  nx = 4
  ny = 4
[]

[MeshModifiers]
  [./subdomain0]
    type = SubdomainBoundingBox
    bottom_left = '0 0 0'
    top_right = '2 1 0'
    block_id = 0
  [../]
  [./subdomain1]
    type = SubdomainBoundingBox
    bottom_left = '0 1 0'
    top_right = '2 2 0'
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
[]

[AuxKernels]
  [./u]
    type = NumbatDarcyVelocity
    variable = u
    pressure = pressure
    gravity = '0 0 0'
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
  [./permeability1]
    type = NumbatPermeability
    permeability = '1 0 0 0 1 0 0 0 1'
    block = 0
  [../]
  [./permeability2]
    type = NumbatPermeability
    permeability = '10 0 0 0 10 0 0 0 10'
    block = 1
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
  file_base = 2D_arithmetic
  print_perf_log = true
[]
