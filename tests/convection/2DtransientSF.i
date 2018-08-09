# Tests the NumbatConvectionSF kernel with a transient executioner

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 1
  nx = 50
[]

[Variables]
  [./concentration]
    initial_condition = 0
  [../]
[]

[AuxVariables]
  [./streamfunction]
  [../]
  [./u]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./u]
    type = NumbatDarcyVelocitySF
    variable = u
    streamfunction = streamfunction
  [../]
[]

[ICs]
  [./streamfunction]
    type = FunctionIC
    variable = streamfunction
    function = 0.001*(1-y)
  [../]
[]

[Kernels]
  [./convection]
    type = NumbatConvectionSF
    variable = concentration
    streamfunction = streamfunction
  [../]
  [./time]
    type = TimeDerivative
    variable = concentration
  [../]
[]

[BCs]
  [./concleft]
    type = DirichletBC
    variable = concentration
    boundary = left
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
  file_base = 2DtransientSF
  execute_on = final
[]
