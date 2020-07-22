///\file run_simulation.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/run_simulation.h"

/// \brief Run through iterations, generate files, and compile video
///
/// Loops through the total number of algorithm iterations (nframes * algsteps)
/// and performs the necessary file handling by calling the subsequent functions
///
/// \param lattice  The 2D grid of spin values
/// \param p  An instance of Ising_Params
///
/// \return void
void run_simulation(int** lattice, Ising_Params &p)
{
    long framenumber;

    mkdir("output", S_IRWXU);
    chdir("output");

    //const char* method = "metropolis";
    void (*step)(int** lattice, Ising_Params &p) = &metropolis_hastings_step;

    //if (method == "metropolis") {
    //    *step = &metropolis_hastings_step;
    //}

    clean();
    // Loop through the desired number of frames
    for (long iter = 0; iter < p.stopiter; iter++)
    {
        if (iter >= p.startiter && (iter - p.startiter) % p.framestep == 0)
        {
            framenumber = (iter - p.startiter) / p.framestep;

            // Save the frame as a png
            lattice2pbm(lattice, p.nrows, p.ncols, framenumber);
            pbm2png(framenumber);
        }

        step(lattice, p);
    }

    pngs2video();
}