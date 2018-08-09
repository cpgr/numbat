# List of available objects

Numbat provides a number of MOOSE objects to simplify the process of simulating density-driven convective mixing in porous media, which are described below.

In addition, as a [MOOSE] application, Numbat also has access to all of the standard MOOSE objects, the complete list of which can be seen in the complete [syntax](syntax/index.md) list.

## Actions

Numbat provides handy actions which automatically add all of the variables, kernels, etc
so that they don't have to be included manually each time. This can significantly reduce the
effort involved in writing a new input file, and also eliminates the possibility of input
file errors due to incorrect parameters.

!syntax list /Numbat

## AuxKernels

In Moose, an AuxKernel is used to enable calculation of a quantity that can be explicitly computed from the solution variables or material properties. An AuxKernel acts on an AuxVariable, and hence returns a single value per node/element.

!syntax list /AuxKernels groups=NumbatApp

## BCs

Boundary conditions are a fundamental MOOSE system, with several common boundary conditions already available in the [MOOSE] framework. Numbat provides two additional boundary conditions that are useful in density-driven convection mixing. In particular, the [NumbatPerturbationBC](/NumbatPerturbationBC.md) can be used to seed the initial instability by applying a random noise to the concentration value at the boundary.

!syntax list /BCs groups=NumbatApp

## DGKernels

DGKernels are used to implement the governing equations using a Discontinuous Galerkin formulation.

!syntax list /DGKernels groups=NumbatApp

## ICs

Several initial conditions are provided in the [MOOSE] framework. Numbat provides an additional initial condition that applies a noise to the initial concentration profile to seed the instability.

!syntax list /ICs groups=NumbatApp

## Kernels

The governing equations are encapsulated in the Numbat Kernels.

!syntax list /Kernels groups=NumbatApp

## Materials

The Materials system provides fluid and rock properties to the Kernels.

!syntax list /Materials groups=NumbatApp

## Mesh

Numbat provides a simple [GeneratedMesh](/GeneratedMesh.md) to enable a regular, orthogonal mesh to be refined at a specified boundary, with a specified resolution.

!syntax list /Mesh groups=NumbatApp

## Postprocessors

A Postprocessor performs an explicit calculation and returns a single value. In Numbat, Postprocessors to calculated the flux over a boundary or total mass of solute in the model are provided, as these quantities are of significant interest in practice.

!syntax list /Postprocessors groups=NumbatApp
