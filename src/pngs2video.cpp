///\file pngs2video.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/pngs2video.h"


/// \brief Uses ffmpeg to create a video from png images
///
/// Uses ffmpeg to convert existing png images into a gif and mp4.
/// The now obsolete png files are then deleted
///
/// \return void
void pngs2video(Ising_Params &p)
{
    char mp4command[0x100];
    snprintf(mp4command, sizeof(mp4command),"ffmpeg -nostats -loglevel 0 -i frame%%d.png %s", (p.outputdir/"output.mp4").c_str());

    char gifcommand[0x100];
    snprintf(gifcommand, sizeof(gifcommand),"ffmpeg -nostats -loglevel 0 -i frame%%d.png %s", (p.outputdir/"output.gif").c_str());

    system(mp4command);
    system(gifcommand);
    system("rm *.png");

}