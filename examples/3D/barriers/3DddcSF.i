# Density-driven convective mixing in a 3D model using the streamfunction
# formulation in a mesh with elliptical barriers
#
# The mesh is created in Gmsh (barrier.geo). To generate the mesh, run 'gmsh -3 barrier.geo'
#
# Ra = 5000

[Mesh]
  type = FileMesh
  file = barrier.msh
[]

[Numbat]
  [./Dimensionless]
    periodic_bcs = false
  [../]
[]

[ICs]
  [./concentration]
    type = NumbatPerturbationIC
    variable = concentration
    amplitude = 0.1
    seed = 1
  [../]
  [./streamfunction_x]
    type = ConstantIC
    variable = streamfunction_x
    value = 0
  [../]
  [./streamfunction_y]
    type = ConstantIC
    variable = streamfunction_y
    value = 0
  [../]
[]

# Boundary condition for barriers (not set up by action)
[BCs]
  [./streamfunxbarrier]
    type = PresetBC
    variable = streamfunction_x
    boundary = barriers
    value = 0
  [../]
  [./streamfunybarrier]
    type = PresetBC
    variable = streamfunction_y
    boundary = barriers
    value = 0
  [../]
  [./Periodic]
    [./x]
      variable = 'concentration streamfunction_x streamfunction_y'
      primary = left
      secondary = right
      translation = '100 0 0'
    [../]
    [./y]
      variable = 'concentration streamfunction_x streamfunction_y'
      primary = front
      secondary = back
      translation = '0 100 0'
    [../]
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
    petsc_options = '-snes_ksp_ew'
    petsc_options_iname = '-ksp_type -pc_type -pc_asm_overlap -sub_pc_type -pc_factor_levels -ksp_atol'
    petsc_options_value = 'gmres asm 10 ilu 4 1e-12'
  [../]
[]

[Executioner]
  type = Transient
  end_time = 6e4
  start_time = 1
  solve_type = NEWTON
  nl_abs_tol = 1e-9
  l_max_its = 200
  [./TimeStepper]
    type = FunctionDT
    interpolate = false
    time_t = '0 10 500 1e3 1e4 6e4'
    time_dt = '9 10 50 100 200 200'
  [../]
[]

[Outputs]
  [./console]
    type = Console
    perf_log = true
    output_nonlinear = true
    output_linear = true
  [../]
  [./exodus]
    type = Exodus
    execute_on = 'INITIAL TIMESTEP_END'
    interval = 4
  [../]
  [./csvoutput]
    type = CSV
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  [./checkpoint]
    type = Checkpoint
    num_files = 2
    interval = 10
  [../]
[]
