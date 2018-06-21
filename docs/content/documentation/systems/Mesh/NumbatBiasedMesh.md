# NumbatBiasedMesh

!syntax description /Mesh/NumbatBiasedMesh

NumbatBiasedMesh produces a generated mesh with a specified refinement at one edge
so that the first element has a width (height) specified using the `refined_resolution` input
parameter.

Each subsequent element increases in width (height) away from the boundary by a fixed
increment $\delta$, so that
\begin{equation}
x_{i+1} = x_i + \delta,
\end{equation}
where the increment $\delta$ is calculated so that the dimensions of the mesh are unchanged.

[fig:biased_mesh] demonstrates the effect of refinement on a simple two-dimensional mesh, where the elements are biased to the top of the mesh.

!media media/biased_mesh.png
       style=width:20%;margin-left:10px
       caption=2D biased mesh
       id=fig:biased_mesh

!syntax parameters /Mesh/NumbatBiasedMesh

!syntax inputs /Mesh/NumbatBiasedMesh

!syntax children /Mesh/NumbatBiasedMesh
