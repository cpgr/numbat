# Tests the porosity given by AuxVariables with no noise

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
[]

[Variables]
  [./concentration]
    initial_condition = 0
  [../]
[]

[AuxVariables]
  [./initial_porosity]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./porosity]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[ICs]
  [./initial_porosity]
    type = ConstantIC
    value = 0.25
    variable = initial_porosity
  [../]
[]

[AuxKernels]
  [./porosity]
    type = MaterialRealAux
    variable = porosity
    property = porosity
  [../]
[]

[Materials]
  [./porosity]
    type = NumbatPorosity
    porosity = initial_porosity
  [../]
  [./diffusivity]
    type = NumbatDiffusivity
    diffusivity = 1e-6
  [../]
[]

[Kernels]
  [./diffusion]
    type = NumbatDiffusion
    variable = concentration
  [../]
[]

[BCs]
  [./conctop]
    type = DirichletBC
    variable = concentration
    boundary = top
    value = 1.0
  [../]
  [./concbottom]
    type = DirichletBC
    variable = concentration
    boundary = bottom
    value = 0.0
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
[]

[Outputs]
  exodus = true
  perf_graph = true
  file_base = porosity_fromvar
  execute_on = timestep_end
[]
