# NumbatBiasedMesh
!syntax description /MeshModifiers/NumbatBiasedMesh

This MeshModifier refines one edge of a regular, orthogonal mesh so that the first
element has a width (height) specified using the `refined_resolution` input parameter.

Each subsequent element increases in width (height) away from the boundary by a fixed
increment $\delta$, so that
\begin{equation}
x_{i+1} = x_i + \delta,
\end{equation}
where the increment $\delta$ is calculated so that the dimensions of the mesh are unchanged.

\ref{fig:biased_mesh} demonstrates the effect of this MeshModifier on a simple two-dimensional mesh, where the elements are biased to the top of the mesh.

!media media/biased_mesh.png width=50% margin-left=10px caption=2D biased mesh id=fig:biased_mesh

!syntax parameters /MeshModifiers/NumbatBiasedMesh

!syntax inputs /MeshModifiers/NumbatBiasedMesh

!syntax children /MeshModifiers/NumbatBiasedMesh
