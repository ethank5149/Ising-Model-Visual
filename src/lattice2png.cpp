///\file lattice2png.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/lattice2png.h"

/// \brief Writes an Ising lattice to a ".pbm" file
///
/// \param lattice
/// \param p
/// \param frame
///
/// \return void
void lattice2png(Ising_Params &p, long frame)
{
    // Appropriately format the numbered filename
    char savefile[0x100];
    snprintf(savefile, sizeof(savefile), "frame%ld.pbm", frame); // Save file as a pbm

    char pbm2pngcommand[0x100]; // Custom ffmpeg command
    snprintf(pbm2pngcommand, sizeof(pbm2pngcommand),
             "ffmpeg -nostats -loglevel 0 -i frame%ld.pbm frame%ld.png && rm frame%ld.pbm",
             frame, frame, frame);


    // Declare and open the file
    FILE* file;
    file = fopen(savefile, "wb");

    // Print the header information for the pbm file
    fprintf(file, "P1\n");
    fprintf(file, "%ld %ld\n", p.nrows, p.ncols);

    // Write data
    for (int i = 0; i < p.nrows * p.ncols; i++)
    {
            fprintf(file, "%d ", (p.lattice[i] == 1 ? 1 : 0));
    }
    fclose(file); // Close the file

    // Use ffmpeg to convert pbm file to a png, then delete the now obsolete pbm file
    system(pbm2pngcommand);
}