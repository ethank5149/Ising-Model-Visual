///\file wolff_step.cpp
///\author Ethan Knox
///\date 7/24/2020.

#include "../include/wolff_step.h"


void wolff_step(int *lattice, Ising_Params &p)
{
    double P = 1.0 - exp(-2.0 * p.J / p.T);
    long choice, chosen;

    int seed = randint(0, p.nrows * p.ncols);
    p.cluster.push_back(seed);

    for (long neighbor : neighbors(p, seed))//For each neighbor
    {
        if (lattice[neighbor] == lattice[seed])//If the spins are parallel
        {
            p.perimeter.push_back(neighbor);//Add it to the perimeter
        }
    }

    while (!p.perimeter.empty()) //While the perimeter list is still full
    {
        choice = randint(0, p.perimeter.size());
        chosen = p.perimeter[choice]; //Pick a random spin from the perimeter list

        if (uniform(0.0, 1.0) < P)//Decide if a bond exists
        {
            if(std::count(p.cluster.begin(), p.cluster.end(), chosen) == 0)//Make sure spin isn't already in the cluster
            {
                p.cluster.push_back(chosen);
                p.perimeter.erase(p.perimeter.begin()+choice);

                for (long neighbor : neighbors(p, chosen))
                {
                    if (lattice[neighbor] == lattice[chosen] /*debug-> &&std::count(p.perimeter.begin(), p.perimeter.end(), neighbor)*/)
                    {
                        p.perimeter.push_back(neighbor);
                    }
                }
            }
            else {p.perimeter.erase(p.perimeter.begin()+choice);}
        }
        else {p.perimeter.erase(p.perimeter.begin()+choice);}

    }

    for (long spin : p.cluster) {lattice[spin] *= -1;}
}
