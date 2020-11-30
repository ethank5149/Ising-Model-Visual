///\file pngs2video.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/pngs2video.h"
#include "../include/clean.h"
#include <boost/process.hpp>
#include <fmt/format.h>
#include <iostream>

///\brief Creates a video of the simulation
///
///Uses ffmpeg to convert the png frames into both a gif and mp4, then the now
///obsolete frames are deleted
///\todo Don't delete these images if future option to save them is selected
///
/// \return void
void pngs2video(Ising &p)
{
    std::cout << "\nCreating mp4... ";
    boost::process::system(fmt::format("ffmpeg -nostats -loglevel 0 -i {0}/frame%d.png {1}", p.outputdir.string(), (p.outputdir/"output.mp4").string()).c_str());
    std::cout << "Done!\n" << std::endl;

    std::cout << "\nCreating gif... ";
    boost::process::system(fmt::format("ffmpeg -nostats -loglevel 0 -i {0}/frame%d.png {1}", p.outputdir.string(), (p.outputdir/"output.gif").string()).c_str());
    std::cout << "Done!\n" << std::endl;

    clean_pngs(p);
}