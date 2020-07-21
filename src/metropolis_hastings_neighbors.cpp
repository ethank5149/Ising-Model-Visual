#include "../include/metropolis_hastings_neighbors.h"

/*!
\brief Calculates the sum of the spins of the neighbors of a specified point

@param lattice  The 2D grid of spin values
@param nrows  Number of rows
@param ncols  Number of columns
@param i  The row in question
@param j  The column in question

\return The resulting sum of spins
*/
int neighbors(int** lattice, int nrows, int ncols, int i, int j)
{
    return lattice[(i + 1) % nrows][j] +
        lattice[i][(j + 1) % ncols] +
        lattice[((i - 1) + nrows) % nrows][j] +
        lattice[i][((j - 1) + ncols) % ncols];
}