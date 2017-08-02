# NumbatConvectionSF
!syntax description /Kernels/NumbatConvectionSF

Implements the weak form of the dimensionless convection equation using the streamfunction formulation
\begin{equation}
\mathbf{u} \cdot \nabla c,
\end{equation}
where $\mathbf{u}$ is the fluid velocity.

In two dimensions, the velocity is given by
\begin{equation}
\mathbf{u} = \left(- \frac{\partial \psi}{\partial y}, \frac{\partial \psi}{\partial x} \right),
\end{equation}
while in three dimensions, it is
\begin{equation}
\mathbf{u} = \left(- \frac{\partial \psi_x}{\partial z}, \frac{\partial \psi_y}{\partial z}, \frac{\partial \psi_y}{\partial x} - \frac{\partial \psi_x}{\partial y} \right).
\end{equation}

!syntax parameters /Kernels/NumbatConvectionSF

!syntax inputs /Kernels/NumbatConvectionSF

!syntax children /Kernels/NumbatConvectionSF
