# Three-dimensional examples

Complete input files for 2D models using the dimensional and dimensionless streamfunction formulations are provided, for both isotropic and anisotropic porous media. These examples
are provided in the Numbat *examples* folder.

## Isotropic models

The first examples are for an isotropic porous medium ($\gamma = 1$).

### Input file

The complete input file for this problem is

!listing examples/3D/isotropic/3Dddc.i

### Running the example

!alert note
    This example should **not** be run on a laptop or workstation
    due to the large computational requirements. Do **not** run this using
    the *Peacock* gui provided by MOOSE.

Examples of the total run times for this problem on a cluster are over
27 hours for a single processor down to only 30 minutes using 100
processors in parallel.

### Results

This 3D example should produce a concentration profile similar to that
presented in [fig:3D], where several downwelling plumes of high
concentration can be observed:

!media media/3D.png
       style=width:80%;margin-left:10px
       caption=3D concentration profile
       id=fig:3D

Note that due to the random perturbation applied to the initial
concentration profile, the geometry of the concentration profile
obtained will differ from run to run.

The flux over the top surface is of particular interest in many cases
(especially convective mixing of CO$_2$). This is calculated in
this example file using the [NumbatSideFlux](/NumbatSideFlux.md) in the input
file, and presented in [fig:3Dflux].

!media media/3Dflux.png
       style=width:80%;margin-left:10px
       caption=3D flux across the top boundary
       id=fig:3Dflux

Initially, the flux is purely diffusive, and scales as
$1 / \sqrt(\pi t)$, where $t$ is time (shown as the dashed green line).
After some time, the convective instability becomes sufficiently strong,
at which point the flux across the top boundary rapidly increases (at a
time of approximately 1,700 seconds). Also shown for comparison is the
flux for the 2D example. It is apparent that the 3D model leads in a
slower onset of convection (the time where the flux first increases from
the diffusive rate).
