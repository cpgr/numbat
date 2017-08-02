# NumbatDarcyVelocitySF
!syntax description /AuxKernels/NumbatDarcyVelocitySF

An AuxKernel to calculate fluid velocity given the streamfunction(s). In two dimensions,
the velocity components $(u,w)$ are related to the streamfunction $\psi$ by
\begin{equation}
u = - \frac{\partial \psi}{\partial z}, \quad w = \frac{\partial \psi}{\partial x}.
\end{equation}

In three dimensions, the velocity components $(u,v,w)$ are given by
\begin{equation}
(u, v, w) = \left( -\frac{\partial \psi_y}{\partial z}, \frac{\partial \psi_x}{\partial z}, \frac{\partial \psi_y}{\partial x} - \frac{\partial \psi_x}{\partial y} \right).
\end{equation}


!syntax parameters /AuxKernels/NumbatDarcyVelocitySF

!syntax inputs /AuxKernels/NumbatDarcyVelocitySF

!syntax children /AuxKernels/NumbatDarcyVelocitySF
