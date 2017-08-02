# NumbatDarcyVelocity
!syntax description /AuxKernels/NumbatDarcyVelocity

An AuxKernel to calculate the fluid velocity given by Darcy's law
\begin{equation}
\mathbf{u} = - \frac{\mathbf{K}}{\mu} \left(\nabla P - \rho(c) \mathbf{g} \right),
\end{equation}
where $\mathbf{K}$ is the permeability, $\mu$ is the fluid viscosity, $P$ is the fluid pressure,
$\rho(c)$ is the fluid density (as a function of concentration) and $\mathbf{g}$ is gravity.

!!! note
    As an AuxKernel can only calculate a scalar, the component of the fluid velocity must
    be specified

!syntax parameters /AuxKernels/NumbatDarcyVelocity

!syntax inputs /AuxKernels/NumbatDarcyVelocity

!syntax children /AuxKernels/NumbatDarcyVelocity
