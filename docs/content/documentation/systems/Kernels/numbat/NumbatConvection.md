# NumbatConvection
!syntax description /Kernels/NumbatConvection

Implements the weak form of
\begin{equation}
\mathbf{u} \cdot \nabla c,
\end{equation}
where the fluid velocity is given by Darcy's law
\begin{equation}
\mathbf{u} = - \frac{\mathbf{K}}{\mu} \left(\nabla P - \rho \mathbf{g} \right),
\end{equation}
where $\mathbf{K}$ is the permeability, $\mu$ is the fluid viscosity, $P$ is the fluid pressure, $\rho$ is the fluid density, and $\mathbf{g}$ is gravity.

!syntax parameters /Kernels/NumbatConvection

!syntax inputs /Kernels/NumbatConvection

!syntax children /Kernels/NumbatConvection
