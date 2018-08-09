# Calculates steady Darcy flux given a prescribed pressure gradient, which
# can be used to calculate the effective permeability
#
# This test has two homogeneous layers, so the effective permeability should
# be equal to the weighted harmonic mean of the permeabilities
# keff = (1 + 1)/(1/1 + 1/10) = 1.818181...

[Mesh]
  type = GeneratedMesh
  dim = 3
  xmax = 2
  ymax = 2
  zmax = 2
  nx = 4
  ny = 4
  nz = 4
[]

[MeshModifiers]
  [./subdomain0]
    type = SubdomainBoundingBox
    bottom_left = '0 0 0'
    top_right = '2 2 1'
    block_id = 0
  [../]
  [./subdomain1]
    type = SubdomainBoundingBox
    bottom_left = '0 0 1'
    top_right = '2 2 2'
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
  [./w]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[AuxKernels]
  [./w]
    type = NumbatDarcyVelocity
    variable = w
    pressure = pressure
    gravity = '0 0 0'
    component = z
  [../]
[]

[Functions]
  [./pic]
    type = ParsedFunction
    value = '2-z/2'
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
    boundary = back
    value = 2.0
  [../]
  [./right]
    type = DirichletBC
    variable = pressure
    boundary = front
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
    boundary = back
  [../]
  [./flux]
    type = SideIntegralVariablePostprocessor
    boundary = back
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
  file_base = 3D_harmonic
  perf_graph = true
[]
