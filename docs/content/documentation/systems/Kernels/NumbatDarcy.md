# NumbatDarcy

!syntax description /Kernels/NumbatDarcy

Implements the weak form of the continuity equation where the velocity is given by Darcy's law
\begin{equation}
\nabla \cdot \mathbf{u},
\end{equation}
where
\begin{equation}
\mathbf{u} = - \frac{\mathbf{K}}{\mu} \left(\nabla P - \rho \mathbf{g} \right),
\end{equation}
where $\mathbf{K}$ is the permeability, $\mu$ is the fluid viscosity, $P$ is the fluid pressure, $\rho$ is the fluid density, and $\mathbf{g}$ is gravity.

!syntax parameters /Kernels/NumbatDarcy

!syntax inputs /Kernels/NumbatDarcy

!syntax children /Kernels/NumbatDarcy
