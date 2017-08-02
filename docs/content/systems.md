# List of available objects

Numbat provides a number of MOOSE objects to simplify the process of simulating density-driven convective mixing in porous media.

## AuxKernels

In Moose, an AuxKernel is used to enable calculation of a quantity that can be explicitly computed from the solution variables or material properties. An AuxKernel acts on an AuxVariable, and hence returns a single value per node/element.

!syntax objects /AuxKernels groups=numbat title=none

## BCs

Boundary conditions are a fundamental MOOSE system, with several common boundary conditions already available in the [MOOSE] framework. Numbat provides two additional boundary conditions that are useful in density-driven convection mixing. In particular, the [NumbatPerturbationBC](/BCs/NumbatPerturbationBC.m) can be used to seed the initial instability by applying a random noise to the concentration value at the boundary.

!syntax objects /BCs groups=numbat title=none

## DGKernels

DGKernels are used to implement the governing equations using a Discontinuous Galerkin formulation.

!syntax objects /DGKernels groups=numbat title=none

## ICs

Several initial conditions are provided in the [MOOSE] framework. Numbat provides an additional initial condition that applies a noise to the initial concentration profile to seed the instability.

!syntax objects /ICs groups=numbat title=none

## Kernels

The governing equations are encapsulated in the Numbat Kernels.

!syntax objects /Kernels groups=numbat title=none

## Materials

The Materials system provides fluid and rock properties to the Kernels.

!syntax objects /Materials groups=numbat title=none

## MeshModifiers

Numbat provides a MeshModifier to enable a regular, orthogonal mesh to be biased at a particular boundary, with a specified resolution.

!syntax objects /MeshModifiers groups=numbat title=none

## Postprocessors

A Postprocessor performs an explicit calculation and returns a single value. In Numbat, Postprocessors to calculated the flux over a boundary or total mass of solute in the model are provided, as these quantities are of significant interest in practice.

!syntax objects /Postprocessors groups=numbat title=none
