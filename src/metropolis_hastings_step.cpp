///\file metropolis_hastings_step.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/metropolis_hastings_step.h"
#include "../include/random_generators.h"
#include <cmath>


///\brief Performs one step of the Metropolis-Hastings Algorithm
///
///Selects a point at random and calculates the energy difference.
///If this difference is less than zero, the spin is automatically flipped,
///otherwise it's flipped with probability \f$ P = e^{-\frac{dE}{k_BT}} \f$
///
///\param p An instance of the Ising class
///
///\return void
void metropolis_hastings_step(Ising &p)
{
    // Select a random point in the lattice
    int idx = uniformintegral(p.nrows*p.ncols);

    // Calculates the change in energy if this spin is flipped
    int neighbor_sum = 0;
    for(int spin : p.neighbors(p.nrows, p.ncols, idx)){
        neighbor_sum += p.lattice[spin];
    }

    double dE = 2 * (p.J * neighbor_sum - p.h) * p.lattice[idx];

    // If the system is in a lower energy state afterwards, immediately accept
    // Otherwise, accept with a probability $P = e^{-\frac{dE}{k_B T}}$
    if ((dE < 0.0) || (uniformfloating(1.0) < exp(-dE / (p.k_B * p.T))))
    {
        p.lattice[idx] *= -1;
    }
}