//
// Created by ethan on 7/22/2020.
//

#include "../include/pngs2video.h"

/*!
\brief Runs a customizable batch script with the intent of converting the
frames into a proper video. The dimensions of the video are passed to the
script as well.

\return void
*/
void pngs2video()
{
    system("ffmpeg -nostats -loglevel 0 -i frame%d.png output.mp4 && rm *.png");
    if (exists("output.mp4"))
    {
        system("ffmpeg -nostats -loglevel 0 -i output.mp4 output.gif");
    }
}