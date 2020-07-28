///\file Ising_Params.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/Ising_Params.h"

//long Ising_Params::flatten(long i, long j) const
//{
//    return this->ncols * i + j;
//}
//
//long Ising_Params::stacki(long i) const
//{
//    return i / this->nrows;
//}
//
//long Ising_Params::stackj(long j) const
//{
//    return j % this->ncols;
//}



Ising_Params::Ising_Params(long input_nrows, long input_ncols, long input_stopiter, long input_framestep,
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

void Ising_Params::randomize()
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
