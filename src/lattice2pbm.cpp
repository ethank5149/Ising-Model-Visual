///\file lattice2pbm.cpp
///\author Ethan Knox
///\date 7/22/2020.

#include "../include/lattice2pbm.h"

/// \brief Writes an Ising lattice to a ".pbm" file
///
/// \param lattice
/// \param nrows
/// \param ncols
/// \param frame
///
/// \return void
void lattice2pbm(int** lattice, int nrows, int ncols, const long frame)
{
    // Appropriately format the numbered filename
    char savefile[0x100];
    snprintf(savefile, sizeof(savefile), "frame%ld.pbm", frame); // Save file as a pbm

    FILE* file;
    file = fopen(savefile, "wb");

    fprintf(file, "P1\n");
    fprintf(file, "%d %d\n", nrows, ncols);
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            fprintf(file, "%d ", (lattice[i][j] == 1 ? 1 : 0));
        }
        fprintf(file, "\n");
    }

    fclose(file);
}