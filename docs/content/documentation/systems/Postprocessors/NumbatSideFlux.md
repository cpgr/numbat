# NumbatSideFlux

!syntax description /Postprocessors/NumbatSideFlux

The mass flux over a boundary is calculated as
\begin{equation}
F = \phi \rho D \nabla c \cdot \mathbf{n},
\end{equation}
where $\phi$ is porosity, $\rho$ is the fluid density, $D$ is the diffusion coefficent, $c$ is concentration, and $\mathbf{n}$ is the normal to the boundary.

!syntax parameters /Postprocessors/NumbatSideFlux

!syntax inputs /Postprocessors/NumbatSideFlux

!syntax children /Postprocessors/NumbatSideFlux
