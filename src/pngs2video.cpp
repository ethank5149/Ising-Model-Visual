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
void pngs2video()
{
    system("ffmpeg -nostats -loglevel 0 -i frame%d.png output.avi && rm *.png");
    if (exists("output.avi"))
    {
        system("ffmpeg -nostats -loglevel 0 -i output.avi output.gif");
    }
}