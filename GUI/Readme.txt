# TBStudio
TBStudio is a technical software package to construct Tight-Binding model for nano-scale materials. It is a powerful and easy to use
software package to construct Tight-Binding (TB) model for nano-scale materials. Starting from the simplified linear combination of
atomic orbitals method in combination with first-principles calculations (such as OpenMX or Vasp packages), one can construct a TB model
in the two-centre approximation. Using Slater and Koster approach we calculate the TB Hamiltonian of the system and use a nonlinear
fitting algorithm to find the best entries for both Hamiltonian and overlap matrices to reproduce the first-principles data. We obtain
expressions for the Hamiltonian and overlap matrix elements between different orbitals (s, p and d orbitals with or without spin-orbit
coupling) for the different atoms and present the SK coefficients in a orthogonal or nonorthogonal basis set. Furthermore, by using
TBStudio one can generate a code in preferred programming language such as C++, C, Fortran, Mathematica, Matlab and Python.

TBStudio is a cross-platform application with a graphical user interface design that is user-friendly and easy to work with. This
application is written in c++. This software is written by wxWidgets including openGL and LAPACK library.

Getting Started
1. TBStudio is provided you as a pre-compiled released (this version was compiled for windows 64-bit processors. win ver > XP). So
there is no need to compile TBStudio. Do not you have 64 bit processor? You can contact developer support to provide you a compatible
version as soon as possible. As mentioned before it is a cross platform software so it is also possible to compile for linux and Mac OS.

2. Launch TBStudio

3. Go to Graphene folder and open the file model.tbm ...

4. Press Start button from Main-Ribbon > Analyze > Fitting. The SK parameters Tab will be shown. In terminal one can monitor the regression
analysis.

5. Now the time for magic! What program language have you written your own Green's Function calculation? Which language do you prefer to
start your code? C++, C, Fortran, Mathematica, Matlab and Python? It does not matter. We generate for you the Hamiltonian in your preferred
programming language. Go to Main-Ribbon > Wizard > Code Generator and generate your own code as C++, C, Fortran, Mathematica, Matlab and Python.

6. Hope you enjoy TBStudio ...






New in Version 1.3.0

1) Spin-Orbit Coupling (SOC) was added to the calculation
2) Code generator supports also SOC, non-orthogonal TB-Model or a system including both of them.
3) We added many examples with their references.
