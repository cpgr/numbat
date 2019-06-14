# This input file is used in the documentation. Please do not alter the
# ordering of these blocks
[Mesh]
  type = NumbatBiasedMesh
  nx = 10
  ny = 10
  dim = 2
  xmax = 1
  refined_resolution = 0.01
[]

[Variables]
  [C1]
    initial_condition = 0
    scaling = 1e6
  []
  [C2]
    initial_condition = 0
    scaling = 1e6
  []
  [pressure]
    initial_condition = 1e6
  []
[]

[AuxVariables]
  [Beta1]
  []
  [Beta2]
  []
  [density]
    family = MONOMIAL
    order = CONSTANT
  []
[]

[Kernels]
  [time1]
    type = NumbatTimeDerivative
    variable = C1
  []
  [time2]
    type = NumbatTimeDerivative
    variable = C2
  []
  [diffusion1]
    type = NumbatDiffusion
    diffusivity_name = d1
    variable = C1
  []
  [diffusion2]
    type = NumbatDiffusion
    diffusivity_name = d2
    variable = C2
  []
  [convection1]
    type = NumbatConvection
    variable = C1
    pressure = 'pressure'
  []
  [convection2]
    type = NumbatConvection
    variable = C2
    pressure = 'pressure'
  []
  [darcy]
    type = NumbatDarcy
    variable = pressure
    concentration = 'C1 C2'
  []
[]

[AuxKernels]
  [Beta1]
    type = NumbatBeta
    temperature = '40'
    pressure = 'pressure'
    variable = Beta1
    coefficients = '0.4 0 0 0 0'
  []
  [Beta2]
    type = NumbatBeta
    temperature = '40'
    pressure = 'pressure'
    variable = Beta2
    coefficients = '-0.1 0 0 0 0'
  []
  [density]
    type = MaterialRealAux
    variable = density
    execute_on = 'TIMESTEP_END INITIAL'
    property = density
  []
[]

[BCs]
  [conctop1]
    type = DirichletBC
    variable = C1
    boundary = 'top'
    value = 0.0125
  []
  [conctop2]
    type = DirichletBC
    variable = C2
    boundary = 'top'
    value = 0.0125
  []
  [Periodic]
    [x]
      variable = 'C1 C2 pressure'
      auto_direction = 'x'
    []
  []
[]

[Postprocessors]
  [boundary_flux1]
    type = NumbatSideFlux
    variable = 'C1'
    boundary = 'top'
    diffusivity_name = d1
  []
  [boundary_flux2]
    type = NumbatSideFlux
    variable = 'C2'
    boundary = 'top'
    diffusivity_name = d2
  []
  [boundary_fluxT]
    type = LinearCombinationPostprocessor
    pp_names = 'boundary_flux1 boundary_flux2'
    pp_coefs = '1 1'
  []
  [total_mass1]
    type = NumbatTotalMass
    variable = 'C1'
  []
  [total_mass2]
    type = NumbatTotalMass
    variable = 'C2'
  []
  [total_massT]
    type = LinearCombinationPostprocessor
    pp_names = 'total_mass1 total_mass2'
    pp_coefs = '1 1'
  []
  [Ra]
    type = NumbatRayleighNumber
    component = y
    gravity = '0 -9.81 0'
    diffusivity_name = d1
  []
[]

[Materials]
  [porosity]
    type = NumbatPorosity
    porosity = '0.1'
  []
  [permeability]
    type = NumbatPermeability
    permeability = '1e-11 0 0 0 1e-11 0 0 0 1e-11'
  []
  [diffusivity1]
    type = NumbatDiffusivity
    diffusivity_name = d1
    diffusivity = '2e-9'
  []
  [diffusivity2]
    type = NumbatDiffusivity
    diffusivity_name = d2
    diffusivity = '1e-9'
  []
  [density]
    type = NumbatDensityMultipleSpecies
    unsaturated_density = 1000
    coefficient = 'Beta1 Beta2'
    concentration = 'C1 C2'
    saturated_concentration = '0.0125 0.0125'
  []
  [viscosity]
    type = NumbatViscosity
    viscosity = 1e-3
  []
[]

[Executioner]
  type = Transient
  end_time = 10
  solve_type = NEWTON
  nl_abs_tol = 1e-14
  nl_max_its = 20
  l_max_its = 100
  dt = 10
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Outputs]
  execute_on = 'TIMESTEP_END'
  csv = true
  file_base = 2D
  perf_graph = true
  exodus = true
[]
