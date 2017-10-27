# NumbatEffectivePermeability
!syntax description /Postprocessors/NumbatEffectivePermeability

This Postprocessor is useful to calculate the effective permeability in a
particular direction for heterogeneous models. This should be used in a
steady simulation with a fixed pressure gradient, from which the flux $Q$ over
a boundary can be used to calculate the effective permeability $k_{\mathrm{eff}}$
using Darcy's law
\begin{equation*}
k_{\mathrm{eff}} = \frac{Q \mu L}{A \Delta p},
\end{equation*}
where $\mu$ is viscosity, $L$ is the length of the model in the direction of flow,
$A$ is the cross-sectional area of the boundary and $\Delta p$ is the pressure
difference across the model.

!!!note:
    This Postprocessor is only really useful to determine the effective
    permeability of a heterogeneous model, and is otherwise not useful in simulations
    of density-driven convection.

!syntax parameters /Postprocessors/NumbatEffectivePermeability

!syntax inputs /Postprocessors/NumbatEffectivePermeability

!syntax children /Postprocessors/NumbatEffectivePermeability
