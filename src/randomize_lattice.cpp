///\file randomize_lattice.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/randomize_lattice.h"

/// \brief Randomizes the spins of the Ising lattice
///
/// \param lattice  The 2D grid of spin values
/// \param nrows  Number of rows
/// \param ncols  Number of columns
///
/// \return void
void randomize_lattice(int** lattice, int nrows, int ncols)
{
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            if (uniform(0.0, 1.0) > 0.5)
            {
                lattice[i][j] = 1;
            }
            else
            {
                lattice[i][j] = -1;
            }
        }
    }
}