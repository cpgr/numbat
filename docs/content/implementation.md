# Implementation details

Numerical simulations of solutal convection rely on seeding the gravitational instability to initiate the convective mixing process. Numerical roundoff will eventually initiate convective mixing, but can significantly overestimate the critical time for the onset of convection.

Instead, it is usual to seed the instability using a prescribed random perturbation in the model. In Numbat, this initial perturbation can be applied in several ways:

- In the dimensional formulation, a random noise sampled from a uniform distribution can be applied to the porosity;
- In the dimensionless streamfunction formulation, an initial perturbation to the diffusive concentration profile can be applied;
- A random fluctuation to the concentration boundary condition can be applied.
