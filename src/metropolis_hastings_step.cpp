///\file metropolis_hastings_step.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/metropolis_hastings_step.h"

/// \brief Performs one step of the Metropolis-Hastings Algorithm
///
/// Selects a point at random and calculates the energy difference.
/// If this difference is less than zero, the spin is automatically flipped,
/// otherwise it's flipped with probability \f$ P = e^{-\frac{dE}{k_BT}} \f$
///
/// \param lattice  The 2D grid of spin values
/// \param p  Instance of an Ising_Params class
///
/// \return void
void metropolis_hastings_step(int* lattice, Ising_Params &p)
{
    // Select a random point in the lattice
    int idx = randint(0, p.nrows*p.ncols);

    // Calculates the change in energy if this spin is flipped
    int neighbor_sum = 0;
    for(int spin : neighbors(p, idx)){
        neighbor_sum += lattice[spin];
    }

    double dE = 2 * (p.J * neighbor_sum - p.h) * lattice[idx];

    // If the system is in a lower energy state afterwards, immediately accept
    // Otherwise, accept with a probability $P = e^{-\frac{dE}{k_B T}}$
    if ((dE < 0.0) || (uniform(0.0, 1.0) < exp(-dE / (p.k_B * p.T))))
    {
        lattice[idx] *= -1;
    }
}