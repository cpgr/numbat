# NumbatAction

!syntax description /Numbat/Dimensional/NumbatAction

## Description

The `NumbatAction` adds all of the nonlinear variables, kernels, aux variables,
aux kernels and postprocessors typically required in a Numbat simulation.

## Input file syntax

This action is called in the input file simply as

!listing tests/2D/2D_action.i block=Numbat

The use of this action is exactly equivalent to the following input file syntax

!listing tests/2D/2D.i start=Variables end=Materials

A specific value for the saturated boundary concentration can optionally be provided

!listing tests/2D/2D_c0_action.i block=Numbat


!syntax parameters /Numbat/Dimensional/NumbatAction
