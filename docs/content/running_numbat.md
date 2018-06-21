# Running the Numbat application

## Commandline

Most often, Numbat will be run from the commandline using

```bash
./numbat-opt -i input.i
```

Numbat (and all MOOSE applications) have a large number of commandline options available to
the user. The complete list can be viewed using the `--help` option

```text
./numbat-opt --help

Usage: ./numbat-opt [<options>]

Options:
  --allow-test-objects                              Register test objects and syntax.
  --type                                            Return the name of the application object.
  --check-input                                     Check the input file (i.e. requires -i <filename>) and quit.
  --color [auto,on,off]                             Whether to use color in console output (default 'on').
  --definition                                      Shows a SON style input definition dump for input validation
  -v --version                                      Print application version
  --distributed-mesh                                The libMesh Mesh underlying MooseMesh should always be a DistributedMesh
  --dump [search_string]                            Shows a dump of available input file syntax.
  --error                                           Turn all warnings into errors
  --error-deprecated                                Turn deprecated code messages into Errors
  -o --error-override                               Error when encountering overridden or parameters supplied multiple times
  -e --error-unused                                 Error when encountering unused input file options
  --half-transient                                  When true the simulation will only run half of its specified transient (ie half the timesteps).  This is useful for testing recovery and restart
  -h --help                                         Displays CLI usage statement.
  -i <input_file>                                   Specify an input file
  --json                                            Dumps input file syntax in JSON format.
  --keep-cout                                       Keep standard output from all processors when running in parallel
  --list-constructed-objects                        List all moose object type names constructed by the master app factory.
  --mesh-only [mesh_file_name]                      Setup and Output the input mesh only (Default: "<input_file_name>_in.e")
  --minimal                                         Ignore input file and build a minimal application with Transient executioner.
  --n-threads=<n>                                   Runs the specified number of threads per process
  --no-color                                        Disable coloring of all Console outputs.
  --no-timing                                       Disabled performance logging. Overrides -t or --timing if passed in conjunction with this flag
  --no-trap-fpe                                     Disable Floating Point Exception handling in critical sections of code when using DEBUG mode.
  --recover [file_base]                             Continue the calculation.  If file_base is omitted then the most recent recovery file will be utilized
  --recoversuffix [suffix]                          Use a different file extension, other than cpr, for a recovery file
  --redirect-stdout                                 Keep standard output from all processors when running in parallel
  -r <n>                                            Specify additional initial uniform refinements for automatic scaling
  --registry                                        Lists all known objects and actions.
  --registry-hit                                    Lists all known objects and actions in hit format.
  --show-controls                                   Shows the Control logic available and executed.
  --show-input                                      Shows the parsed input file before running the simulation.
  --show-outputs                                    Shows the output execution time information.
  --split-file [filename]                           optional name of split mesh file(s) to write/read
  --split-mesh [splits]                             comma-separated list of numbers of chunks to split the mesh into
  --start-in-debugger <debugger>                    Start the application and attach a debugger.  This will launch xterm windows using the command you specify for 'debugger'
  --stop-for-debugger [seconds]                     Pauses the application during startup for the specified time to allow for connection of debuggers.
  --syntax                                          Dumps the associated Action syntax paths ONLY
  -t --timing                                       Enable all performance logging for timing purposes. This will disable all screen output of performance logs for all Console objects.
  --trap-fpe                                        Enable Floating Point Exception handling in critical sections of code.  This is enabled automatically in DEBUG mode
  --use-split                                       use split distributed mesh files
  -w --warn-unused                                  Warn about unused input file options
  --yaml                                            Dumps input file syntax in YAML format.

Solver Options:
  See solver manual for details (Petsc or Trilinos)
```

### Recovering

If you output checkpoint files (using `checkpoint = true` in your Outputs block) then the `--recover` option will allow you to continue a solve that died in the middle of the solve. This can allow you to recover a job that was killed because the power went out or your job ran out of time on the cluster you were using.

We recommend that all input files for large Numbat simulations enable checkpointing. This can be
enabled using

!listing tests/2D/2DSF_recover.i block=Outputs

For all of the options available for checkpointing, see the [MOOSE] documentation.

If a long-running simulation does fail to complete, it can be recovered by

```bash
./numbat-opt --recover checkpoint_dir/XXXX -i input.i
```

where `checkpoint_dir` is the subdirectory where the checkpoint files are saved, and `XXXX` is the number of one of the available checkpoint files.

### Overriding parameters

MOOSE provides a handy feature where any parameter in the input file can be overridden from
the commandline, making it possible to script studies where only parameters are changed from
simulation to simulation.

For example, assume that the anisotropy `gamma` of the porous medium is set as `1` in the input file

```bash
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
