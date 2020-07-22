//
// Created by ethan on 7/22/2020.
//

#include "../include/pbm2png.h"

/*!
\brief Converts a pbm file into a png and deletes the parent file in order to save space

@param frame  The index of the frame being converted

\return void
*/
void pbm2png(const long frame)
{
    char convertcommand[0x100];

    snprintf(convertcommand, sizeof(convertcommand),
             "ffmpeg -nostats -loglevel 0 -i frame%ld.pbm frame%ld.png && rm frame%ld.pbm",
             frame, frame, frame);
    system(convertcommand);
}