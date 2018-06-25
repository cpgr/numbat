// Gmsh geometry file for a 3D mesh corresponding to
// Ra = 5000 (dimensionless model).
// The mesh is refined at the top boundary with element
// size increasing with depth.
//
// This geometry file can be converted to a mesh using
// gmsh -3 Ra5000.geo

// Mesh width in each dimension
xmax = 2000;
ymax = 2000;
zmax = 5000;

// Resolution at the top and bottom
lctop = 10;
lcbot = 200;

// Vertices of mesh
Point(1) = {0, 0, 0, lcbot};
Point(2) = {xmax, 0, 0, lcbot};
Point(3) = {0, ymax, 0, lcbot};
Point(4) = {xmax, ymax, 0, lcbot};
Point(5) = {xmax, ymax, zmax, lctop};
Point(6) = {xmax, 0, zmax, lctop};
Point(7) = {0, ymax, zmax, lctop};
Point(8) = {0, 0, zmax, lctop};

// Lines connecting vertices
Line(1) = {3, 7};
Line(2) = {7, 5};
Line(3) = {5, 4};
Line(4) = {4, 3};
Line(5) = {3, 1};
Line(6) = {2, 4};
Line(7) = {2, 6};
Line(8) = {6, 8};
Line(9) = {8, 1};
Line(10) = {1, 2};
Line(11) = {8, 7};
Line(12) = {6, 5};

// Surfaces defined by lines
Line Loop(13) = {7, 8, 9, 10};
Plane Surface(14) = {13};
Line Loop(15) = {6, 4, 5, 10};
Plane Surface(16) = {15};
Line Loop(17) = {3, 4, 1, 2};
Plane Surface(18) = {17};
Line Loop(19) = {12, -2, -11, -8};
Plane Surface(20) = {19};
Line Loop(21) = {7, 12, 3, -6};
Plane Surface(22) = {21};
Line Loop(23) = {9, -5, 1, -11};
Plane Surface(24) = {23};
Surface Loop(25) = {14, 22, 20, 18, 16, 24};

// Volume defined by surfaces
Volume(26) = {25};

// Make the sides suitable for periodic boundary conditions
Periodic Surface {18} = {14} Translate {0, ymax, 0};
Periodic Surface {22} = {24} Translate {xmax, 0, 0};

// Name the faces for easy application of boundary conditions
Physical Surface("top") = {20};
Physical Surface("bottom") = {16};
Physical Surface("front") = {14};
Physical Surface("back") = {18};
Physical Surface("left") = {24};
Physical Surface("right") = {22};
Physical Volume("0") = {26};
