[Mesh]
   type = GeneratedMesh
   dim = 3
   nx = 2
   ny = 3
   nz = 4
[]

[Variables]
  [./concentration]
    order = FIRST
    family = LAGRANGE
  [../]
  [./streamfunctionx]
    order = FIRST
    family = LAGRANGE
  [../]
  [./streamfunctiony]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./ThreeDDarcyDDCx]
    type = DarcyDDC
    variable = streamfunctionx
    concentration_variable = concentration
    component = x
    gamma = 0.5
  [../]
  [./ThreeDDarcyDDCy]
    type = DarcyDDC
    variable = streamfunctiony
    concentration_variable = concentration
    component = y
    gamma = 0.5
  [../]
  [./ThreeDConvectionDiffusionDDC]
    type = ConvectionDiffusionDDC
    variable = concentration
    streamfunction_variable = 'streamfunctionx streamfunctiony'
    anisotropic_tensor = '0.5 0 0 0 0.5 0 0 0 1'
  [../]
  [./TimeDerivative]
    type = TimeDerivative
    variable = concentration
  [../]
[]

[BCs]
  [./conctop]
    type = DirichletBC
    variable = concentration
    boundary = 'top'
    value = 1.0
  [../]
  [./streamfunxtop]
    type = DirichletBC
    variable = streamfunctionx
    boundary = 'top'
    value = 0.0
  [../]
  [./streamfunxbottom]
    type = DirichletBC
    variable = streamfunctionx
    boundary = 'bottom'
    value = 0.0
  [../]
  [./streamfunytop]
    type = DirichletBC
    variable = streamfunctiony
    boundary = 'top'
    value = 0.0
  [../]
  [./streamfunybottom]
    type = DirichletBC
    variable = streamfunctiony
    boundary = 'bottom'
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
  type = Transient
  end_time = 1
  solve_type = NEWTON
[]

[ICs]
  [./concentrationIC]
    type = RandomIC
    min = 0
    max = 1
    variable = concentration
  [../]
  [./streamfunctionxIC]
    type = RandomIC
    min = -1
    max = 1
    variable = streamfunctionx
  [../]
  [./streamfunctionyIC]
    type = RandomIC
    min = -1
    max = 1
    variable = streamfunctiony
  [../]
[]
