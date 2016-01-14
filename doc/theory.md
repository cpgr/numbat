Governing equations
=====

Numbat implements the Boussinesq approximation to model density-driven convective mixing in porous media. The governing equations are the convection-diffusion equation.

The governing equations for density-driven flow in porous media are Darcy's law
$$
\begin{equation}
\mathbf{u} = - \frac{\mathbf{K}}{\mu} \left(\nabla P + \rho(c) g \hat{\mathbf{k}} \right),
\label{eq:darcy}
\end{equation}
$$
where $$\mathbf{u} = (u, v, w)$$ is the velocity vector, $$\mathbf{K}$$ is permeability, $$\mu$$ is the fluid viscosity, $$P$$ is the fluid pressure, $$\rho(c)$$ is the fluid density as a function of solute concentration $$c$$, $$g$$ is gravity, and $$\hat{\mathbf{k}}$$ is the unit vector in the $$z$$ direction.

The fluid velocity must also satisfy the continuity equation
$$
\begin{equation}
\nabla \cdot \mathbf{u} = 0,
\end{equation}
$$
and the solute concentration is governed by the convection - diffusion equation
$$
\begin{equation}
\phi \frac{\partial c}{\partial t} + \mathbf{u} \cdot \nabla c = \phi D \nabla^2 c,
\label{eq:convdiff}
\end{equation}
$$
where $$\phi$$ is the porosity, $$t$$ is time and $$D$$ is the diffusivity.

Darcy's law and the convection-diffusion equations are coupled through the fluid density, which is given by
$$
\begin{equation}
\rho(c) = \rho_0 + \frac{c}{c_0} \Delta \rho,
\label{eq:density}
\end{equation}
$$
where $$c_0$$ is the equilibrium concentration, and $$\Delta \rho$$ is the increase in density of the fluid at equilibrium concentration.

The boundary conditions are
$$
\begin{align}
w = 0,&  \quad z = 0, -H, \\
\frac{\partial c}{\partial z} = 0,& \quad z = -H, \\
c = c_0,& \quad z = 0,
\end{align}
$$
which correspond to impermeable boundary conditions at the top and bottom boundaries ($$z = 0$$ and $$z=-H$$, respectively), and a saturated condition at the top boundary.

Initially, there is no solute in the model
$$
\begin{equation}
c = 0, \quad t = 0.
\end{equation}
$$

The solution of the governing equations differs in 2D and 3D. As a result, we shall consider the two cases separately.

### 2D model ###
