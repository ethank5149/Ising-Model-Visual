///\file run_simulation.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/run_simulation.h"
#include "../include/metropolis_hastings_step.h"
#include "../include/wolff_step.h"
#include "../include/lattice2png.h"
#include "../include/pngs2video.h"
#include "../include/clean.h"
#include <iostream>

/// \brief Run through iterations, generate files, and compile video
///
/// Loops through the total number of algorithm iterations (nframes * algsteps)
/// and performs the necessary file handling by calling the subsequent functions
///
/// \param lattice  The 2D grid of spin values
/// \param p  An instance of Ising_Params
///
/// \return void
void run_simulation(Ising &p)
{
    long framenumber;

    if(boost::filesystem::create_directory(p.outputdir)) { std::cout << "\nCreated 'Output' Directory\n" << std::endl; }
    clean_all(p);

    void (*step)(Ising &);
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
            lattice2png(p, framenumber);

            std::cout << "Saving frame " << framenumber + 1 << " out of " << p.stopiter / p.framestep << std::endl;
        }
        // TODO: When trying a 1000x1000 grid, we segfault here
        step(p);
    }

    pngs2video(p);
}