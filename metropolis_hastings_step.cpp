#include "metropolis_hastings_neighbors.h"
#include "metropolis_hastings_step.h"
#include <cmath>
#include <random>


/*!
\brief Performs one step of the Metropolis-Hastings Algorithm

Selects a point at random and calculates the energy difference.
If this difference is less than zero, the spin is automatically flipped,
otherwise it's flipped with probability \f$P = e^{-\frac{dE}{k_BT}} \f$

@param lattice  The 2D grid of spin values
@param nrows  Number of rows
@param ncols  Number of columns
@param nframes  The number of frames desired to visualize the system
@param algsteps  The number of algorithm steps between each recorded frame
@param J  Ferromagnetic Coupling Constant
@param h  Magnetic field strength
@param T  Temperature

\return void
*/
//void metropolis_hastings_step(int** lattice, int nrows, int ncols, double J, double h, double T)
//{
//    // Select a random point in the lattice
//    int i = rand() % nrows;
//    int j = rand() % ncols;
//
//    // Calculates the change in energy if this spin is flipped
//    double dE = 2 * (J * neighbors(lattice, nrows, ncols, i, j) - h) * lattice[i][j];
//
//    // If the system is in a lower energy state afterwards, immediately accept
//    if (dE < 0.0)
//    {
//        lattice[i][j] *= -1;
//    }
//    // Otherwise, accept with a probability $P = e^{-\frac{dE}{k_B T}}$
//    else if (prob() < exp(-dE / (k_B * T)))
//    {
//        lattice[i][j] *= -1;
//    }
//}