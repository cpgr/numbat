# Tests the NumbatConvectionSF kernel with a transient executioner

[Mesh]
  type = GeneratedMesh
  dim = 3
  zmax = 1
  nz = 50
[]

[Variables]
  [./concentration]
    initial_condition = 0
  [../]
[]

[AuxVariables]
  [./streamfunctionx]
  [../]
  [./streamfunctiony]
  [../]
  [./w]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./w]
    type = NumbatDarcyVelocitySF
    variable = w
    streamfunction = 'streamfunctionx streamfunctiony'
    component = z
  [../]
[]

[ICs]
  [./streafunctionx]
    type = FunctionIC
    variable = streamfunctionx
    function = 0.001*(y-1)
  [../]
  [./streamfunctiony]
    type = ConstantIC
    variable = streamfunctiony
    value = 0
  [../]
[]

[Kernels]
  [./convection]
    type = NumbatConvectionSF
    variable = concentration
    streamfunction = 'streamfunctionx streamfunctiony'
  [../]
  [./time]
    type = TimeDerivative
    variable = concentration
  [../]
[]

[BCs]
  [./conctop]
    type = DirichletBC
    variable = concentration
    boundary = front
    value = 1
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
  dt = 10
  solve_type = NEWTON
  end_time = 500
[]

[VectorPostprocessors]
  [./conc]
    type = NodalValueSampler
    variable = concentration
    sort_by = id
  [../]
[]

[Outputs]
  csv = true
  perf_graph = true
  file_base = 3DtransientSF
  execute_on = final
[]
