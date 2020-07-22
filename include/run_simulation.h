//
// Created by ethan on 7/22/2020.
//

#ifndef ISINGMODEL_VISUAL_RUN_SIMULATION_H
#define ISINGMODEL_VISUAL_RUN_SIMULATION_H

#include "sys/stat.h"
#include "unistd.h"

#include "ising_struct.h"
#include "metropolis_hastings_step.h"
#include "file_management.h"
#include "lattice2pbm.h"
#include "pbm2png.h"
#include "pngs2video.h"

void run_simulation(int** lattice, ising_params &p);

#endif //ISINGMODEL_VISUAL_RUN_SIMULATION_H
