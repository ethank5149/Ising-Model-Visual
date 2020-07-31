///\file pngs2video.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/pngs2video.h"
#include "../include/clean.h"
#include <boost/process.hpp>
#include <fmt/format.h>
#include <iostream>

/// \brief Uses ffmpeg to create a video from png images
///
/// Uses ffmpeg to convert existing png images into a gif and mp4.
/// The now obsolete png files are then deleted
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