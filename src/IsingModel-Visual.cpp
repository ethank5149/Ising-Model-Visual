#include <cstdio>
#include <cstdlib>

#include "../include/Ising_Params.h"
#include "../include/run_simulation.h"


int main(int argc, const char* argv[])
{
    long nrows, ncols, stopiter, framestep;
    double J, h, T;
    char method, geometry;

    printf("\n2D ISING MODEL - VISUAL SIMULATION\n");
    printf(  "----------------------------------\n");

    // Check the number of parameters to enable shortcut usage
    if (argc == 2)
    {
        printf("Getting Parameters From File...\n");

        FILE* file;
        file = fopen(argv[1], "r");

        fscanf(file, "%*s %*s %ld", &nrows);
        fscanf(file, "%*s %*s %ld", &ncols);
        fscanf(file, "%*s %*s %ld", &stopiter);
        fscanf(file, "%*s %*s %ld", &framestep);
        fscanf(file, "%*s %*s %lf", &J);
        fscanf(file, "%*s %*s %lf", &h);
        fscanf(file, "%*s %*s %lf", &T);
        fscanf(file, "%*s %*s %s", &method);
        fscanf(file, "%*s %*s %s", &geometry);
        // TODO: nrows changes after assigning geometry?

        fclose(file);
        printf("Done!\n\n");
    }

    else if (argc == 11)
    {
        // Convert commandline arguments from strings
        char** endptr = nullptr;
        nrows = strtol(argv[1], endptr, 0);
        ncols = strtol(argv[2], endptr, 0);
        stopiter = strtol(argv[4], endptr, 0);
        framestep = strtol(argv[5], endptr, 0);
        J = strtod(argv[6], endptr);
        h = strtod(argv[7], endptr);
        T = strtod(argv[8], endptr);
        method = argv[9][0];
        geometry = argv[10][0];
    }
    else
    {
        printf("\nShortcut Usage: %s [nrows] [ncols] [startiter] [stopiter] [framestep] [J] [h] [T]\n\n", argv[0]);

        printf("Number of Rows ------------------> ");
        scanf("%ld", &nrows);

        printf("Number of Columns ---------------> ");
        scanf("%ld", &ncols);

        printf("Stopping Iteration --------------> ");
        scanf("%ld", &stopiter);

        printf("Iterations Between Frames -------> ");
        scanf("%ld", &framestep);

        printf("Ferromagnetic Coupling Constant -> ");
        scanf("%lf", &J);

        printf("Magnetic Field Strength ---------> ");
        scanf("%lf", &h);

        printf("Temperature ---------------------> ");
        scanf("%lf", &T);

        printf("Method --------------------------> ");
        scanf("%s", &method);

        printf("Geometry --------------------------> ");
        scanf("%s", &geometry);
    }
    std::cout << nrows << std::endl;
    Ising_Params p = Ising_Params(nrows, ncols, stopiter, framestep, J, h, T, method, geometry);
    std::cout << p.nrows << std::endl;
    std::cout << "Using the " << (p.method == 'M' ? "Metropolis-Hastings" : "Wolff") << " Algorithm" << std::endl;
    std::cout << "With " << (p.geometry == 'S' ? "Standard Square" : "Hexagonal") << " Geometry" << std::endl;
    std::cout << p.nrows << "x" << p.ncols << " Grid" << std::endl;
    std::cout << p.stopiter << " Iterations, " << p.framestep << " Steps Between Frames" << std::endl;
    std::cout << "J = " << p.J << ", h = " << p.h << ", T = " << p.T << std::endl;
    std::cout << "\nRunning..." << std::endl;

    p.randomize();
    run_simulation(p); // Go baby go

    printf("Done!\n");
    printf("----------------------------------\n");

    return 0;
}
