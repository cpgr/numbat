# NumbatSFAction

!syntax description /Numbat/Dimensionless/NumbatSFAction

## Description

The `NumbatSFAction` adds all of the nonlinear variables, kernels, aux variables,
aux kernels and postprocessors typically required in a dimensionless Numbat simulation.

## Input file syntax

This action is called in the input file simply as

!listing tests/2D/2DSF_action.i block=Numbat

The use of this action is exactly equivalent to the following input file syntax for a 2D
simulation.

!listing tests/2D/2DSF.i start=Variables end=Executioner

!syntax parameters /Numbat/Dimensionless/NumbatSFAction
