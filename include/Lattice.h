//
// Created by ethan on 7/24/2020.
//

#ifndef ISINGMODEL_VISUAL_LATTICE_H
#define ISINGMODEL_VISUAL_LATTICE_H

#include <cstdlib>
#include "random_generators.h"

class Lattice {
private:
    int _rows, _cols;
    int* _spins;
public:
    int rows, cols;

    Lattice(int, int);

    int operator()(int);
    int operator()(int, int);

    void flip(int);
    void flip(int, int);

    void randomize();
};


#endif //ISINGMODEL_VISUAL_LATTICE_H
