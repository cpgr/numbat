# Background theory

## Governing equations

Numbat implements the Boussinesq approximation to model density-driven
convective mixing in porous media. To reduce the computational burden, only a single fluid phase is considered. This is a simplification to the actual physical process, where a gas phase may be present. This simplification is often used in practice, see [citet:emami-meybodi2015] for a discussion about the use of this simplifying assumption.

!alert note
The more complicated two-phase model can be implemented using the `porous_flow` module

The governing equations for density-driven flow in porous media are
Darcy's law
\begin{equation}
\label{eq:darcy}
\mathbf{u} = - \frac{\mathbf{K}}{\mu} \left(\nabla P - \rho(c) g \hat{\mathbf{k}} \right),
\end{equation}
where $\mathbf{u} = (u, v, w)$ is the velocity vector, $\mathbf{K}$ is
permeability, $\mu$ is the fluid viscosity, $P$ is the fluid pressure,
$\rho(c)$ is the fluid density as a function of solute concentration
$c$, $g$ is gravity, and $\hat{\mathbf{k}}$ is the unit vector in the
$z$ direction.

The fluid velocity must also satisfy the continuity equation
\begin{equation}
\nabla \cdot \mathbf{u} = 0,
\end{equation}
and the solute concentration is governed by the convection - diffusion
equation

\begin{equation}
\label{eq:convdiff}
\phi \frac{\partial c}{\partial t} + \mathbf{u} \cdot \nabla c = \phi D \nabla^2 c,
\end{equation}
where $\phi$ is the porosity, $t$ is time and $D$ is the diffusivity.

Darcy's law and the convection-diffusion equations are coupled through
the fluid density, which is given by
\begin{equation}
\label{eq:density}
\rho(c) = \rho_0 + \frac{c}{c_0} \Delta \rho,
\end{equation}
where $c_0$ is the equilibrium concentration, and $\Delta \rho$ is the
increase in density of the fluid at equilibrium concentration.

The boundary conditions are
\begin{equation}
\begin{aligned}
w = 0,&  \quad z = 0, -H, \\
\frac{\partial c}{\partial z} = 0,& \quad z = -H, \\
c = c_0,& \quad z = 0,
\end{aligned}
\end{equation}
which correspond to impermeable boundary conditions at the top and
bottom boundaries, given by $z = 0$ and $z=-H$, respectively, and a
saturated condition at the top boundary.

Initially, there is no solute in the model
\begin{equation}
c = 0, \quad t = 0.
\end{equation}

Numbat solves [eq:darcy] and [eq:convdiff] with density coupled to concentration as in  [eq:density].

## Dimensionless formulation

The governing equations can also be solved using a streamfunction formulation in
2D and a vector potential formulation in 3D. As a result, we shall
consider the two cases separately.

### 2D solution

If we consider an anisotropic model, with vertical and horizontal
permeabilities given by $k_z$ and $k_x$, respectively, we can
non-dimensionalise the governing equations in 2D following [citet:ennis-king2005]. Defining the anisotropy
ratio $\gamma$ as
\begin{equation}
\label{eq:gamma}
\gamma = \frac{k_z}{k_x},
\end{equation}
we scale the variables using
\begin{equation}
\label{eq:scales}
\begin{aligned}
x = \frac{\phi \mu D}{k_z \Delta \rho g \gamma^{1/2}} \hat{x}, \quad z =  \frac{\phi \mu D}{k_z \Delta \rho g} \hat{z}, \quad u = \frac{k_z \Delta \rho g}{\mu \gamma^{1/2}} \hat{u}, \quad w = \frac{k_z \Delta \rho g}{\mu} \hat{w} \\
t = \left(\frac{\phi \mu}{k_z \Delta \rho g}\right)^2 \hat{t}, \quad c = c_0 \hat{c}, \quad P = \frac{\mu \phi D}{k_z}\hat{P},
\end{aligned}
\end{equation}
where $\hat{x}$ refers to a dimensionless variable. The governing
equations in dimensionless form are then
\begin{equation}
\label{eq:darcydim}
\mathbf{u} = - \left(\nabla P + c \mathbf{\hat{k}}\right),
\end{equation}
\begin{equation}
\label{eq:ctydim}
\mathbf{u} = 0,
\end{equation}
\begin{equation}
\label{eq:condiffdim}
\frac{\partial c}{\partial t} + \mathbf{u} \cdot \nabla c = \gamma \frac{\partial^2 c}{\partial x^2} + \frac{\partial^2 c}{\partial z^2},
\end{equation}
where we have dropped the hat on the dimensionless variables for
brevity.

The dimensionless boundary conditions are
\begin{equation}
\label{eq:dimbc}
\begin{aligned}
w = 0,&  \quad z = 0, -Ra, \\
\frac{\partial c}{\partial z} = 0,& \quad z = -Ra, \\
c = 1,& \quad z = 0,
\end{aligned}
\end{equation}
where $Ra$ is the Rayleigh number, defined as
\begin{equation}
\label{eq:ra}
Ra = \frac{k_z \Delta \rho g H}{\phi \mu D}.
\end{equation}
In this form, the Rayleigh number only appears in the boundary
conditions as the location of the lower boundary. Therefore, $Ra$ can be
interpreted in this formalism as a dimensionless model height, and can
be varied in simulations by simply changing the height of the mesh.

Finally, the dimensionless initial condition is
\begin{equation}
\label{eq:ic}
c = 0, \quad t = 0.
\end{equation}
For isotropic models, where $k_x = k_z$ and hence $\gamma = 1$, we
recover the dimensionless equations given by [citet:slim2014].

The coupled governing equations must be solved numerically. To simplify
the numerical analysis, we introduce the streamfunction $\psi(x,z,t)$
such that
\begin{equation}
\label{eq:2Dstreamfunction}
u = - \frac{\partial \psi}{\partial z}, \quad w = \frac{\partial \psi}{\partial x}.
\end{equation}
This definition satisfies the continuity equation, [eq:ctydim], immediately.

The pressure $P$ is removed from [eq:darcydim] by taking the
curl of both sides and noting that $\nabla \times \nabla P = 0$ for any
$P$, to give
\begin{equation}
\label{eq:darcypsi}
\nabla^2 \psi = - \frac{\partial c}{\partial x},
\end{equation}
where we have introduced the streamfunction $\psi$ using [eq:2Dstreamfunction].

The convection-diffusion equation, [eq:condiffdim] becomes
\begin{equation}
\label{eq:condiffpsi}
\frac{\partial c}{\partial t} - \frac{\partial \psi}{\partial z} \frac{\partial c}{\partial x} + \frac{\partial \psi}{\partial x} \frac{\partial c}{\partial z} = \gamma \frac{\partial^2 c}{\partial x^2} + \frac{\partial^2 c}{\partial z}.
\end{equation}
The boundary conditions become
\begin{equation}
\label{eq:bcpsi}
\begin{aligned}
\frac{\partial \psi}{\partial x} = 0,&  \quad z = 0, -Ra, \\
\frac{\partial c}{\partial z} = 0,& \quad z = -Ra, \\
c = 1,& \quad z = 0,
\end{aligned}
\end{equation}
while the initial condition is still given by [eq:ic].

In two dimensions, Numbat solves [eq:darcypsi] and [eq:condiffpsi].

### 3D solution

We now consider the case of a three-dimensional model. For simplicity,
we consider the case where all lateral permeabilities are equal
($k_y = k_x$). The governing equations for the 3D model are identical to
the 2D model. In dimensionless form, they are given by [eq:darcydim] to
[eq:condiffdim], with boundary conditions
given by [eq:dimbc], and initial condition given by [eq:ic].

To solve these governing equations in 3D, a different approach must be
used as the streamfunction $\psi$ is not defined in three dimensions.
Instead, we define a vector potential $\Psi = (\psi_x, \psi_y, \psi_z)$
such that
\begin{equation}
\label{eq:Psi}
\mathbf{u} = \nabla \times \Psi.
\end{equation}
It is important to note that the vector potential is only known up to
the addition of the gradient of a scalar $\zeta$ as
\begin{equation}
\nabla \times \left( \Psi + \nabla \zeta \right) = \nabla \times \Psi \quad \forall \zeta,
\end{equation}
as $\nabla \times \nabla \zeta = 0$ for any scalar $\zeta$. This
uncertainty is referred to as guage freedom, and is common in
electrodynamics. Taking the curl of [eq:darcydim] and
substituting [eq:Psi], we have
\begin{equation}
\nabla(\nabla \cdot \Psi) - \nabla^2 \Psi = \left(- \frac{\partial c}{\partial y}, \frac{\partial c}{\partial x}, 0\right),
\end{equation}
where we have again used the fact that $\nabla \times \nabla P = 0$. If
we choose $\nabla \cdot \Psi = 0$ to specify the guage condition, this
simplifies to
\begin{equation}
\label{eq:poisson}
\nabla^2 \Psi = \left(\frac{\partial c}{\partial y},  -\frac{\partial c}{\partial x}, 0\right).
\end{equation}
As shown in [citet:e1997],
$\nabla \cdot \Psi = 0$ is satisfied throughout the domain if
\begin{equation}
\begin{aligned}
\psi_x = \psi_y = 0,& \quad z = 0, -Ra,  \\
\frac{\partial \psi_z}{\partial z} = 0, & \quad  z = 0, -Ra.
\end{aligned}
\end{equation}
The governing equations are then
\begin{equation}
\label{eq:darcy3d}
\nabla^2 \Psi = \left(\frac{\partial c}{\partial y}, -\frac{\partial c}{\partial x}, 0 \right),
\end{equation}
\begin{equation}
\label{eq:convdiff3d}
\frac{\partial c}{\partial t} + \mathbf{u} \cdot \nabla c = \gamma \left( \frac{\partial^2 c}{\partial x^2} + \frac{\partial^2 c}{\partial y^2} \right) + \frac{\partial^2 c}{\partial z^2},
\end{equation}
where the continuity is satisfied automatically because
$\nabla \cdot \left( \nabla \times \Psi \right) = 0$ for any $\Psi$.

Finally, it is straightforward to show that $\psi_z = 0$ in order to
satisfy $\nabla^2 \psi_z = 0$ and
$\frac{\partial \psi_z}{\partial z} = 0$, which means that the vector
potential has only $x$ and $y$ components,
\begin{equation}
\Psi = (\psi_x, \psi_y, 0),
\end{equation}
and therefore the fluid velocity $\mathbf{u} = (u, v, w)$ is
\begin{equation}
\mathbf{u} = \left( -\frac{\partial \psi_y}{\partial z}, \frac{\partial \psi_x}{\partial z}, \frac{\partial \psi_y}{\partial x} - \frac{\partial \psi_x}{\partial y} \right).
\end{equation}
Note that if there is no $y$ dependence, [eq:darcy3d] and
\eqref{eq:convdiff3d} reduce to
\begin{equation}
\begin{aligned}
\nabla^2 \Psi = \, & \left(0, -\frac{\partial c}{\partial x}, 0 \right), \\\\
\frac{\partial c}{\partial t} + \mathbf{u} \cdot \nabla c = \, & \gamma \frac{\partial^2 c}{\partial x^2}  + \frac{\partial^2 c}{\partial z^2}.
\end{aligned}
\end{equation}
It is simple to show that $\nabla^2 \psi_x = 0$ and $\psi_x = 0$ at
$z = 0, -Ra$ are only satisfied if $\psi_x = 0$ in the entire domain. In
this case, the governing equations reduce to the two-dimensional
formulation, as expected.

In three dimensions, Numbat solves [eq:darcy3d] and [eq:convdiff3d].

!bibtex bibliography
