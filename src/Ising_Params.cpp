///\file Ising_Params.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/Ising_Params.h"


long Ising_Params::flatten(long i, long j) const
{
    return this->ncols * i + j;
}

long Ising_Params::stacki(long i) const
{
    return i / this->nrows;
}

long Ising_Params::stackj(long j) const
{
    return j % this->ncols;
}


Ising_Params::Ising_Params()
{
    if(method == 'W'){ // We only need this if the Wolff algorithm was chosen
        perimeter.reserve(4 * nrows * ncols);
        cluster.reserve(nrows*ncols);
    }
}
