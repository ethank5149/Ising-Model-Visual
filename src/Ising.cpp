///\file Ising.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/Ising.h"
#include "../include/random_generators.h"
#include "../include/sqr_neighbors.h"
#include "../include/hex_neighbors.h"

Ising::Ising(long input_nrows, long input_ncols, long input_stopiter, long input_framestep,
        double input_J, double input_h, double input_T, char input_method, char input_geometry)
{
    nrows = input_nrows;
    ncols = input_ncols;
    stopiter = input_stopiter;
    framestep = input_framestep;
    J = input_J;
    h = input_h;
    T = input_T;
    method = input_method;
    geometry = input_geometry;
    lattice = (int *)malloc(nrows * ncols * sizeof(int));

    if(method == 'W'){ // We only need this if the Wolff algorithm was chosen
        perimeter.reserve(4 * nrows * ncols);
        cluster.reserve(nrows*ncols);
    }

    neighbors = (geometry == 'H' ? &hex_neighbors : &sqr_neighbors);
}

void Ising::randomize() const
{
    for (int i = 0; i < nrows * ncols; i++)
    {
        if (uniformfloating(1.0) > 0.5)
        {
            lattice[i] = 1;
        }
        else
        {
            lattice[i] = -1;
        }
    }
}
