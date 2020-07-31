///\file wolff_step.cpp
///\author Ethan Knox
///\date 7/24/2020.

#include "../include/wolff_step.h"
#include "../include/random_generators.h"
#include <utility>
#include <algorithm>

void wolff_step(Ising &p)
{
    double P = 1.0 - exp(-2.0 * p.J / p.T);
    size_t chosen;

    size_t seed = uniformintegral(p.nrows * p.ncols);
    p.cluster.insert(seed);

    for (size_t neighbor : p.neighbors(p.nrows, p.ncols, seed))//For each neighbor
    {
        if (p.lattice[neighbor] == p.lattice[seed])//If the spins are parallel
        {
            p.perimeter.insert(neighbor);//Add it to the perimeter
        }
    }

    while (!p.perimeter.empty()) //While the perimeter list is still full
    {
        chosen = *std::next(p.perimeter.begin(), uniformintegral(p.perimeter.size())); //Pick a random spin from the perimeter list
        p.perimeter.erase(chosen); //We don't need it in the perimeter anymore

        if (uniformfloating(1.0) < P)//Decide if a bond exists
        {
            p.cluster.insert(chosen); // Move it to the cluster

            for (size_t neighbor : p.neighbors(p.nrows, p.ncols, chosen)) // For each of this new spin's neighbors
            {
                if (p.lattice[neighbor] == p.lattice[seed]) // See if they're parallel to the seed
                {
                    if(!p.cluster.count(neighbor)){ // Dont add it to the perimeter if its already in the cluster
                        p.perimeter.insert(neighbor); // Add them to the perimeter as well
                    }
                }
            }
        }
    }

    for (size_t spin : p.cluster) {p.lattice[spin] *= -1;} // Flip all these spins

    p.cluster.clear();}
