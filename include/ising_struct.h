//
// Created by ethan on 7/21/2020.
//

#ifndef ISINGMODEL_VISUAL_ISING_STRUCT_H
#define ISINGMODEL_VISUAL_ISING_STRUCT_H

struct ising_params{
    int nrows;
    int ncols;
    int startiter;
    int stopiter;
    int framestep;
    double J;
    double h;
    double T;
};

#endif //ISINGMODEL_VISUAL_ISING_STRUCT_H
