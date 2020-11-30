///\headerfile Ising.h
///\author Ethan Knox
///\date 7/22/2020.

#ifndef ISINGMODEL_VISUAL_ISING_H
#define ISINGMODEL_VISUAL_ISING_H

///\class Ising
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

#include <boost/filesystem.hpp>
#include <unordered_set>
#include <vector>

class Ising
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

    std::vector<long> (*neighbors)(long, long, long){};

    void randomize() const;

    Ising(long, long, long, long, double, double, double, char, char);
};

#endif //ISINGMODEL_VISUAL_ISING_H
