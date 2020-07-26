///\headerfile metropolis_hastings_step.h
///\author Ethan Knox
///\date 7/22/2020.

#ifndef ISINGMODEL_VISUAL_METROPOLIS_HASTINGS_STEP_H
#define ISINGMODEL_VISUAL_METROPOLIS_HASTINGS_STEP_H

#include <cmath>

#include "random_generators.h"
#include "metropolis_hastings_neighbors.h"
#include "Ising_Params.h"

void metropolis_hastings_step(int* lattice, Ising_Params &p);

#endif //ISINGMODEL_VISUAL_METROPOLIS_HASTINGS_STEP_H
