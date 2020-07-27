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
#include <filesystem>
#include <iostream>

class Ising_Params
{
public:
    int nrows{};
    int ncols{};
    int startiter{};
    std::unordered_set<long> cluster{};
    std::unordered_set<long> perimeter{};
    long stopiter{};
    long framestep{};
    double J{};
    double h{};
    double T{};
    double k_B = 1.0;
    char method{};

    std::filesystem::path outputdir = std::filesystem::current_path() / "output";
    std::filesystem::path tempdir = std::filesystem::temp_directory_path();

    Ising_Params();

    long flatten(long, long) const;
    long stacki(long) const;
    long stackj(long) const;
};

#endif //ISINGMODEL_VISUAL_ISING_PARAMS_H
