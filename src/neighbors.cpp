//
// Created by ethan on 7/25/2020.
//

#include "../include/neighbors.h"


std::vector<long> neighbors(Ising_Params &p, long idx)
{
    return std::vector<long>{p.flatten((p.stacki(idx) + 1 + p.nrows) % p.nrows, (p.stackj(idx) + 0 + p.ncols) % p.ncols),
                          p.flatten((p.stacki(idx) + 0 + p.nrows) % p.nrows, (p.stackj(idx) + 1 + p.ncols) % p.ncols),
                          p.flatten((p.stacki(idx) - 1 + p.nrows) % p.nrows, (p.stackj(idx) + 0 + p.ncols) % p.ncols),
                          p.flatten((p.stacki(idx) + 0 + p.nrows) % p.nrows, (p.stackj(idx) - 1 + p.ncols) % p.ncols)};
}