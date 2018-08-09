# Calculates steady Darcy flux given a prescribed pressure gradient, which
# can be used to calculate the effective permeability
#
# This test has a homogeneous permeability, so the effective permeability should
# be equal to the given permeability
# keff = 1

[Mesh]
  type = GeneratedMesh
  dim = 3
  ny = 4
  nx = 4
  nz = 4
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
    component = x
  [../]
[]

[Functions]
  [./pic]
    type = ParsedFunction
    value = '2-x'
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
    prop_values = '10 0.1'
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
  file_base = 3D_homogeneous
  perf_graph = true
  csv = true
[]
