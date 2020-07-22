//
// Created by ethan on 7/21/2020.
//

#include "../include/file_management.h"
#include <cstdio>
#include <cstdlib>
#include "sys/stat.h"


int exists(const char* fname)
{
    struct stat buffer{};
    int exist = stat(fname, &buffer);
    if (exist == 0)
        return 1;
    else // -1
        return 0;
}

void clean()
{
    if (exists("frame0.pbm"))
    {
        system("rm *.pbm");
    }
    if (exists("frame0.png"))
    {
        system("rm *.png");
    }

    if (exists("output.mp4"))
    {
        system("rm output.mp4");
    }

    if (exists("output.gif"))
    {
        system("rm output.gif");
    }
}