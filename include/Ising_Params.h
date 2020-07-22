//
// Created by ethan on 7/22/2020.
//

#ifndef ISINGMODEL_VISUAL_ISING_PARAMS_H
#define ISINGMODEL_VISUAL_ISING_PARAMS_H


class Ising_Params {
public:
    int nrows{};
    int ncols{};
    int startiter{};
    long stopiter{};
    long framestep{};
    double J{};
    double h{};
    double T{};
    double k_B = 1.0;
};


#endif //ISINGMODEL_VISUAL_ISING_PARAMS_H
