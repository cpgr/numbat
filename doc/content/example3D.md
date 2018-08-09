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

## Large model

Increasing the size of the mesh enables more of the flow regimes to be modelled (at the cost
of increased computational expense). Consider a dimensionless model with Rayleigh number $Ra = 5000$. Lateral model dimensions are chosen so that approximately twenty fingers in the lateral directions are present at the onset of convection.

A suitable fully unstructured mesh for this model that is sufficiently refined near the
top boundary with increasing element size with depth to minimise the number of elements can
be constructed in an external meshing code. In this example, the open-source mesh generator
[Gmsh](http://www.gmsh.info) is used. The following geometry file describes the dimensions
of the model and the target resolutions.

!listing examples/3D/isotropic/Ra5000.geo

This mesh geometry file can be used to generate a mesh using Gmsh, either through its
graphical user interface, or alternatively, on the commandline

```bash
gmsh -3 Ra5000.geo
```

which results in a mesh file with approximately 8.4 million tetrahedral elements.

### Input file

The complete input file for this problem is

!listing examples/3D/isotropic/3DddcSF_Ra5000.i

An example of the evolution of the convective fingers in this model are presented in [fig:3Da] and [fig:3Db] for an isotropic model. The concentration profile just after the onset of convection is shown in  [fig:3Da] for a dimensionless time $t = 1400$. As the isosurface shows, there are a large number of small fingers at this stage. As time increases, these small structures merge, forming larger fingers in a process that continues as time proceeds, until only a few large fingers are present, see  [fig:3Db]. This merging behaviour is very complicated and difficult to characterise in any quantitative manner

!media media/3Da.png
       style=width:80%;margin-left:10px
       caption=Evolution of convective mixing in 3D. Time is dimensionless.
       id=fig:3Da

!media media/3Db.png
      style=width:80%;margin-left:10px
      caption=Evolution of convective mixing in 3D (continued). Time is dimensionless.
      id=fig:3Db

Many interesting observations can be made from large-scale 3D models. For example, the temporal
evolution of the fingers shown in [fig:3Da] and [fig:3Db] can also be examined through a horizontal
slice through the model, see [fig:slices]. In this example, a horizontal slice is taken at a dimensionless distance of 100 from the top surface (where the CO$_2$ concentration is 1). As the fingers approach this depth, they are initially observed as circular regions of higher concentration, cf [fig:slices] (a) and (b), where we can see that the fingers have just reached this depth at dimensionless time 1000. As time increases, the complexity of the fingering process can be observed, with merging of adjacent fingers and growth observed. Like [citet:pau2010] and [citet:fu2013], we observe that the fingers arrange themselves into polygonal structures with thin profiles surrounded by large regions of unsaturated fluid, see [fig:slices] (d), (e) and (f).

!media media/slices.png
      style=width:90%;margin-left:10px
      caption=Horizontal slice at dimensionless depth 10 showing the evolution of the convective fingers in 3D. Time increasing from (a) to (f).
      id=fig:slices

!bibtex bibliography
