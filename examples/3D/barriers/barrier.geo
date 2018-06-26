// Generated 16:14 23-01-2018
// Barrier statistics
//  Number: 2
//  Volume fraction: 0.00640762848573
//  Major axis: (mean) 20, (std) 2
//  Minor axis: (mean) 10, (std) 2

SetFactory("OpenCASCADE");

// Maximum dimensions
xmax = 100;
ymax = 100;
zmax = 100;

// Resolution at the top and bottom
lctop = 5;
lcbot = 20;

// Resolution at the internal barriers
lcbar = 5;

// Vertices of mesh
Point(1) = {0, 0, 0, lcbot};
Point(2) = {xmax, 0, 0, lcbot};
Point(3) = {0, ymax, 0, lcbot};
Point(4) = {xmax, ymax, 0, lcbot};
Point(5) = {xmax, ymax, zmax, lctop};
Point(6) = {xmax, 0, zmax, lctop};
Point(7) = {0, ymax, zmax, lctop};
Point(8) = {0, 0, zmax, lctop};

// Lines
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

// Surfaces
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

// Volume
vbox = newv;
Volume(vbox) = {25};

// Add elliptical barriers
b = news;
Disk(b) = {60.6696512922, 33.4915065169, 76.4357058097, 20.4396856573, 10.0130747499};
Extrude{0, 0, lcbar}{ Surface{b}; }

b = news;
Disk(b) = {35.2247013571, 55.6741137888, 48.6485346749, 17.8387226331, 11.3942126143};
Extrude{0, 0, lcbar}{ Surface{b}; }

// Total number of barriers
numb = 2;

// Set characteristic length of points in the barriers
Characteristic Length { PointsOf{ Volume{vbox+1:vbox+numb}; } } = lcbar;

v = newv;
BooleanDifference(v) = {Volume{vbox}; Delete;} {Volume{vbox+1:vbox+numb}; Delete;};

// After the BooleanDifference, the surfaces get renumbered by Gmsh. The surfaces parallel to the x-z
// plane are now labelled 1 and 4 for y = 0 and y = ymax, respectively. Similarly, the surfaces
// parallel to the y-z plane are labelled 4 and 2 for x = 0 and x = xmax, respectively.
// Make the sides suitable for periodic boundary conditions
Periodic Surface {6} = {1} Translate {0, ymax, 0};
Periodic Surface {2} = {4} Translate {xmax, 0, 0};

// Name the faces
Physical Surface("top") = {3};
Physical Surface("bottom") = {5};
Physical Surface("right") = {2};
Physical Surface("left") = {4};
Physical Surface("front") = {1};
Physical Surface("back") = {6};

// Name the barriers
Physical Surface("barriers") = {7:news};

// Name the volume
Physical Volume("0") = {v};
