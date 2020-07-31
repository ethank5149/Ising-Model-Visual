///\file lattice2png.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/lattice2png.h"
#include <boost/process.hpp>
#include <fmt/core.h>
#include <iostream>

/// \brief Writes an Ising lattice to a ".pbm" file
///
/// \param lattice
/// \param p
/// \param frame
///
/// \return void
void lattice2png(Ising &p, long frame)
{
    boost::filesystem::path savefile{p.outputdir / fmt::format("frame{}.pbm", frame)};
    boost::filesystem::ofstream file(savefile);

    // Print the header information for the pbm file
    file <<  "P1\n";
    file << p.nrows << " " << p.ncols << "\n";

    // Write data
    for (int i = 0; i < p.nrows * p.ncols; i++)
    {
            file << (p.lattice[i] == 1 ? 1 : 0) << " ";
    }

    file.close();

    // Use ffmpeg to convert pbm file to a png, then delete the now obsolete pbm file
    boost::process::system(
            fmt::format(
                    "ffmpeg -nostats -loglevel 0 -i {0}/frame{1}.pbm {0}/frame{1}.png",
                    p.outputdir.string(), frame).c_str());
    boost::filesystem::remove(savefile);

}