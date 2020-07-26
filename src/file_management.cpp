///\file file_management.cpp
///\author Ethan Knox
///\date 7/21/2020.

#include "../include/file_management.h"
#include <cstdio>
#include <cstdlib>
#include "sys/stat.h"

///\brief Checks to see if a file or directory exists
///
/// \param fname
/// \return 1/0 (true/false)
int exists(const char* fname)
{
    struct stat buffer{};
    int exist = stat(fname, &buffer);
    if (exist == 0)
        return 1;
    else // -1
        return 0;
}

///\brief Checks to see if previous output files exists, and deletes them if so
///
/// \return void
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

    if (exists("output.avi"))
    {
        system("rm output.avi");
    }

    if (exists("output.gif"))
    {
        system("rm output.gif");
    }
}