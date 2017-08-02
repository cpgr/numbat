# NumbatDensity
!syntax description /Materials/NumbatDensity

The density is given by
\begin{equation}
\rho(c) = \rho_0 + \frac{c \Delta \rho}{c_0},
\end{equation}
where $\rho_0$ is the density at zero solute concentration, $c$ is the concentration of solute, $\Delta \rho$ is the density increase at full saturation, and $c_0$ is the equilibrium solute concentration.

These parameters are specified in the input file as `zero_density` ($\rho_0$), `delta_density` ($\Delta \rho$), and `saturated_concentration` ($c_0$).

!syntax parameters /Materials/NumbatDensity

!syntax inputs /Materials/NumbatDensity

!syntax children /Materials/NumbatDensity
