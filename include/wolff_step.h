//
// Created by ethan on 7/24/2020.
//

#ifndef ISINGMODEL_VISUAL_WOLFF_STEP_H
#define ISINGMODEL_VISUAL_WOLFF_STEP_H

#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include "random_generators.h"
#include "Ising_Params.h"
#include "wolff_neighbors.h"

void wolff_step(int**, Ising_Params &);

#endif //ISINGMODEL_VISUAL_WOLFF_STEP_H
