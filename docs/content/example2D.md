# 2D examples

Complete input files for 2D models using the dimensional and dimensionless streamfunction formulations are provided, for both isotropic and anisotropic porous media. These examples
are provided in the Numbat *examples* folder.

## Isotropic models

The first 2D examples are for an isotropic porous medium ($\gamma = 1$).

### Input file

The complete input file for this problem is

!listing examples/2D/isotropic/2Dddc.i

### Running the example

This example can be run on the commandline using

```bash
numbat-opt -i 2Dddc.i
```

Alternatively, this file can be run using the *Peacock* gui provided by
MOOSE using

```bash
peacock -i 2Dddc.i
```

in the directory where the input file *2Dddc.i* resides.

### Results

This 2D example should take only a few minutes to run to completion,
producing a concentration profile similar to that presented in [fig:2D],
where several downwelling plumes of high concentration can be observed after 3528 s:

!media media/2D.png
       style=width:80%;margin-left:10px
       caption=2D concentration profile (t = 3528 s)
       id=fig:2D

The flux per unit width over the top boundary is of particular interest in many cases
(especially convective mixing of $\textrm{CO}_2$). This is calculated using the *boundaryfluxint* postprocessor in the input file, and presented in \ref{fig:2Dflux}.

!media media/2Dflux.png
       style=width:80%;margin-left:10px
       caption=2D flux across the top boundary
       id=fig:2Dflux

Initially, the flux is purely diffusive, and scales as
$1 / \sqrt(\pi t)$, where $t$ is time (shown as the dashed red line).
After some time, the convective instability becomes sufficiently strong,
at which point the flux across the top boundary rapidly increases (at a
time of approximately 2000 seconds).

## Anisotropic models

The second 2D example is for an anisotropic porous medium with
$\gamma = 0.75$ (ie., the vertical permeability is three quarters of the horizontal
permeability).

### Input file

!listing examples/2D/anisotropic/2Dddc.i

Note that the permeability anisotropy is introduced in the kernels using the *gamma* and *anisotropic_tensor* input parameters.

### Running the example

This example can be run on the commandline using

```bash
numbat-opt -i 2Dddc_anisotropic.i
```

Alternatively, this file can be run using the *Peacock* gui provided by
MOOSE using

```bash
peacock -i 2Dddc_anisotropic.i
```

in the directory where the input file *2Dddc_anisotropic.i* resides.

### Results

This 2D example should take only a few minutes to run to completion,
producing a concentration profile similar to that presented in [fig:2Da],
where several downwelling plumes of high concentration can be observed after 5000 s:

!media media/2Danisotropic.png
       style=width:80%;margin-left:10px
       caption=2D concentration profile for $\gamma = 0.75$ (t = 5000 s)
       id=fig:2Da

In comparison to the isotropic example (with $\gamma = 1$) presented in [fig:2D], we note that the concentration profile in the anisotropic example
has only reached a similar depth after 5000 s (compared to 3528 s). The effect of the reduced vertical permeability in the anisotropic example slows the convective transport.

This observation can be quantified by comparing the flux per unit width over the top boundary of both examples, see [fig:2Dfluxcomp].

!media media/2Dfluxcomp.png
       style=width:80%;margin-left:10px
       caption=Comparison of the 2D flux across the top boundary
       id=fig:2Dfluxcomp

The inclusion of permeability anisotropy delays the onset of convection in comparison to the isotropic example, from a time of approximately 2000 seconds in the isotropic example
to approximately 3500 seconds in the anisotropic example.
