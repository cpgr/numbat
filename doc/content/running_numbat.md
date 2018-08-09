# Running the Numbat application

## Commandline

Most often, Numbat will be run from the commandline using

```bash
./numbat-opt -i input.i
```

Numbat (and all MOOSE applications) have a large number of commandline options available to
the user. The complete list can be viewed using the `--help` option

```bash
./numbat-opt --help
```

### Recovering

If you output checkpoint files (using `checkpoint = true` in your Outputs block) then the `--recover` option will allow you to continue a solve that died in the middle of the solve, perhaps because the job ran out of time on the cluster you were using.

We recommend that all input files for large Numbat simulations enable checkpointing. This can be
enabled using

!listing tests/2D/2DSF_recover.i block=Outputs

For all of the options available for checkpointing, see the [MOOSE] documentation.

If a long-running simulation does fail to complete, it can be recovered by running

```bash
./numbat-opt --recover checkpoint_dir/XXXX -i input.i
```

where `checkpoint_dir` is the subdirectory where the checkpoint files are saved, and `XXXX` is the number of one of the available checkpoint files.

### Overriding parameters

MOOSE provides a handy feature where any parameter in the input file can be overridden from
the commandline, making it possible to script studies where only parameters are changed from
simulation to simulation.

For example, assume that the anisotropy `gamma` of the porous medium is set as `1` in the input file

```text
[Kernels]
  [./Darcy]
    type = NumbatDarcySF
    variable = streamfunction
    concentration = concentration
    gamma = 1
  [../]
[]
```

This value can be changed to `0.5` by running Numbat with the following commandline option

```bash
./numbat-opt -i input.i Kernels/Darcy/gamma=0.5
```

## Graphical user interface (Peacock)

MOOSE provides a graphical user interface, Peacock, which can be used to both run simulations and create input files. Starting Peacock from within the base Numbat directory allows
Peacock to extract the Numbat syntax, so that all Numbat objects are available in the
menus.

!alert note
It is not recommended to use Peacock to run very large models (e.g. three dimensional simulations)
