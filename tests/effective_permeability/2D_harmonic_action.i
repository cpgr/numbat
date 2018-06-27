# Calculates steady Darcy flux given a prescribed pressure gradient, which
# can be used to calculate the effective permeability
#
# This test has two homogeneous layers, so the effective permeability should
# be equal to the weighted harmonic mean of the permeabilities
# keff = (1 + 1)/(1/1 + 1/10) = 1.818181...

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
    top_right = '1 2 0'
    block_id = 0
  [../]
  [./subdomain1]
    type = SubdomainBoundingBox
    bottom_left = '1 0 0'
    top_right = '2 2 0'
    block_id = 1
  [../]
[]

[Numbat]
  [./EffectivePermeability]
    boundary_inflow = left
    boundary_outflow = right
    pressure_inflow = 2
    pressure_outflow = 1
    direction = x
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
  nl_abs_tol = 1e-14
  nl_rel_tol = 1e-12
[]

[Outputs]
  execute_on = TIMESTEP_END
  csv = true
  file_base = 2D_harmonic
  print_perf_log = true
[]
