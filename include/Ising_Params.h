///\file Ising_Params.h
///\author Ethan Knox
///\date 7/22/2020.

#ifndef ISINGMODEL_VISUAL_ISING_PARAMS_H
#define ISINGMODEL_VISUAL_ISING_PARAMS_H

///\class Ising_Params
///
///\brief Stores all pertinent info regarding the simulation
///
///\param nrows  Number of rows
///\param ncols  Number of columns
///\param nframes  The number of frames desired to visualize the system
///\param algsteps  The number of algorithm steps between each recorded frame
///\param J  Ferromagnetic Coupling Constant
///\param h  Magnetic field strength
///\param T  Temperature

#include <unordered_set>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>

#include "../include/random_generators.h"
#include "../include/sqr_neighbors.h"
#include "../include/hex_neighbors.h"

class Ising_Params
{
public:
    long nrows{};
    long ncols{};
    long stopiter{};
    long framestep{};
    double J{};
    double h{};
    double T{};
    double k_B = 1.0;
    char method{};
    char geometry{};
    int * lattice{};


    std::unordered_set<long> cluster{};
    std::unordered_set<long> perimeter{};

    boost::filesystem::path outputdir = boost::filesystem::current_path() / "output";
    boost::filesystem::path tempdir = boost::filesystem::temp_directory_path();

    std::vector<long> (*neighbors)(long, long, long){};

    void randomize();

    Ising_Params(long, long, long, long, double, double, double, char, char);
};

#endif //ISINGMODEL_VISUAL_ISING_PARAMS_H
