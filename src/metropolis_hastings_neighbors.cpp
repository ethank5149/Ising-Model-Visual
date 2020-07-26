///\file metropolis_hastings_neighbors.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/metropolis_hastings_neighbors.h"

/// \brief Calculates the sum of the spins of the neighbors of a specified point
///
/// \param lattice  The 2D grid of spin values
/// \param nrows  Number of rows
/// \param ncols  Number of columns
/// \param i  The row in question
/// \param j  The column in question
///
/// \return The resulting sum of spins
int metropolis_hastings_neighbors(int* lattice, Ising_Params &p, long idx)
{
    return lattice[neighbors(p, idx)[0]] +
           lattice[neighbors(p, idx)[1]] +
           lattice[neighbors(p, idx)[2]] +
           lattice[neighbors(p, idx)[3]];
}