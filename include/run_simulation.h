///\headerfile run_simulation.h
///\author Ethan Knox
///\date 7/22/2020.

#ifndef ISINGMODEL_VISUAL_RUN_SIMULATION_H
#define ISINGMODEL_VISUAL_RUN_SIMULATION_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem>
#include <iostream>
#include <stdlib.h>

#include "Ising_Params.h"
#include "metropolis_hastings_step.h"
#include "wolff_step.h"
#include "lattice2pbm.h"
#include "pbm2png.h"
#include "pngs2video.h"


void run_simulation(int* lattice, Ising_Params &p);

#endif //ISINGMODEL_VISUAL_RUN_SIMULATION_H
