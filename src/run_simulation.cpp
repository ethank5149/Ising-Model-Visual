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
void run_simulation(int* lattice, Ising_Params &p)
{
    long framenumber;
    mkdir(p.outputdir.c_str(), S_IRWXU);
    std::filesystem::current_path(p.tempdir);

    // If a run was quit early and a temporary directory is reused, it might not be empty.
    // If so, empty it manually to overcome pesky permission errors (At least in Unix).
    if(!std::filesystem::is_empty(p.tempdir)){
        system("rm *.png");
        system("rm *.pbm");
    }
    std::filesystem::remove(p.outputdir/"output.mp4");
    std::filesystem::remove(p.outputdir/"output.gif");

    void (*step)(int *, Ising_Params &);
    if (p.method == 'M') {
        step = &metropolis_hastings_step;
    }
    else if(p.method == 'W'){
        step = &wolff_step;
    }

    // Loop through the desired number of frames
    for (long iter = 0; iter < p.stopiter; iter++)
    {
        if (iter % p.framestep == 0)
        {
            framenumber = iter / p.framestep;

            // Save the frame as a png
            lattice2pbm(lattice, p, framenumber);
            pbm2png(framenumber);
        }
        // TODO: When trying a 1000x1000 grid, we segfault here
        step(lattice, p);
    }

    pngs2video(p);
}