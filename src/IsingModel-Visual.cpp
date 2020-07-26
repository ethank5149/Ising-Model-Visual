#include <cstdio>
#include <cstdlib>

#include "../include/Ising_Params.h"
#include "../include/randomize_lattice.h"
#include "../include/run_simulation.h"


int main(int argc, const char* argv[])
{
    Ising_Params p{};

    printf("\n2D ISING MODEL - VISUAL SIMULATION\n");
    printf(  "----------------------------------\n");

    // Check the number of parameters to enable shortcut usage
    if (argc == 2)
    {
        printf("Getting Parameters From File...\n");

        FILE* file;
        file = fopen(argv[1], "r");

        fscanf(file, "%*s %*s %d", &p.nrows);
        fscanf(file, "%*s %*s %d", &p.ncols);
        fscanf(file, "%*s %*s %d", &p.startiter);
        fscanf(file, "%*s %*s %ld", &p.stopiter);
        fscanf(file, "%*s %*s %ld", &p.framestep);
        fscanf(file, "%*s %*s %lf", &p.J);
        fscanf(file, "%*s %*s %lf", &p.h);
        fscanf(file, "%*s %*s %lf", &p.T);
        fscanf(file, "%*s %*s %s", &p.method);

        fclose(file);
        printf("Done!\n\n");
    }

    else if (argc == 9)
    {
        // Convert commandline arguments from strings
        char** endptr = nullptr;
        p.nrows = atoi(argv[1]);
        p.ncols = strtol(argv[2], endptr, 0);
        p.startiter = strtol(argv[3], endptr, 0);
        p.stopiter = strtol(argv[4], endptr, 0);
        p.framestep = strtol(argv[5], endptr, 0);
        p.J = strtod(argv[6], endptr);
        p.h = strtod(argv[7], endptr);
        p.T = strtod(argv[8], endptr);
        p.method = argv[9][0];
    }
    else
    {
        printf("\nShortcut Usage: %s [nrows] [ncols] [startiter] [stopiter] [framestep] [J] [h] [T]\n\n", argv[0]);

        printf("Number of Rows ------------------> ");
        scanf("%d", &p.nrows);

        printf("Number of Columns ---------------> ");
        scanf("%d", &p.ncols);

        printf("Starting Iteration --------------> ");
        scanf("%d", &p.startiter);

        printf("Stopping Iteration --------------> ");
        scanf("%ld", &p.stopiter);

        printf("Iterations Between Frames -------> ");
        scanf("%ld", &p.framestep);

        printf("Ferromagnetic Coupling Constant -> ");
        scanf("%lf", &p.J);

        printf("Magnetic Field Strength ---------> ");
        scanf("%lf", &p.h);

        printf("Temperature ---------------------> ");
        scanf("%lf", &p.T);

        printf("Method --------------------------> ");
        scanf("%s", &p.method);
    }

    printf("Parameters:\n");
    printf("nrows, ncols = %d, %d\n", p.nrows, p.ncols);
    printf("startiter, stopiter, framestep = %d, %ld, %ld\n", p.startiter, p.stopiter, p.framestep);
    printf("J, h, T = %f, %f, %f\n", p.J, p.h, p.T);
    printf("Method = %c\n\n", p.method);

    printf("Running...\n");

    int* lattice = (int*)malloc(p.nrows*p.ncols * sizeof(int));

    randomize_lattice(lattice, p.nrows, p.ncols);
    run_simulation(lattice, p); // Go baby go
    free(lattice);

    printf("Done!\n");
    printf("----------------------------------\n");

    return 0;
}
