Governing equations
=====

Numbat implements the Boussinesq approximation to model density-driven convective mixing in porous media. The governing equations are the convection-diffusion equation.

The governing equations for density-driven flow in porous media are Darcy's law
$$
\mathbf{u} = - \frac{\mathbf{K}}{\mu} \left(\nabla P + \rho(c) g \hat{\mathbf{k}} \right),
\label{eq:darcy}
$$
where $\mathbf{u} = (u, v, w)$ is the velocity vector, $\mathbf{K}$ is permeability, $\mu$ is the fluid viscosity, $P$ is the fluid pressure, $\rho(c)$ is the fluid density as a function of solute concentration $c$, $g$ is gravity, and $\hat{\mathbf{k}}$ is the unit vector in the $z$ direction.
