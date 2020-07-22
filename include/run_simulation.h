///\headerfile run_simulation.h
///\author Ethan Knox
///\date 7/22/2020.

#ifndef ISINGMODEL_VISUAL_RUN_SIMULATION_H
#define ISINGMODEL_VISUAL_RUN_SIMULATION_H

#include "sys/stat.h"
#include "unistd.h"

#include "ising_struct.h"
#include "metropolis_hastings_step.h"
#include "file_management.h"
#include "../include/lattice2pbm.h"
#include "pbm2png.h"
#include "pngs2video.h"

void run_simulation(int** lattice, Ising_Params &p);

#endif //ISINGMODEL_VISUAL_RUN_SIMULATION_H
