#include "stdio.h"
#include "stdlib.h"
#include "math.h"

/*!
\def kB
\brief Boltzmann constant
*/
#define kB 1.0

// Function Declarations
void pbms2images();
void images2video(int**, int, int);
void lattice2pbm(int**, int, int, int);
double prob();
int neighbors(int**, int, int, int, int);
void initialize_lattice(int**, int, int);
void metropolis_hastings_step(int**, int, int, int, int, double, double, double);
void run_simulation(int**, int, int, int, int, double, double, double);


int main(int argc, const char* argv[])
{
    printf("\n2D ISING MODEL - VISUAL SIMULATION\n");
    printf("----------------------------------\n");

    // Check the number of parameters to enable shortcut usage
    if (argc == 8) {
        // Convert commandline arguments from strings
        char** endptr = NULL;
        int nrows = strtol(argv[1], endptr, 0);
        int ncols = strtol(argv[2], endptr, 0);
        int nframes = strtol(argv[3], endptr, 0);
        int algsteps = strtol(argv[4], endptr, 0);
        double J = strtod(argv[5], endptr);
        double h = strtod(argv[6], endptr);
        double T = strtod(argv[7], endptr);

        printf("\nRunning...\n");

        int** lattice = (int**)malloc(nrows * sizeof(int*));
        for (int i = 0; i < nrows; i++) {
            lattice[i] = (int*)malloc(ncols * sizeof(int));
        }

        initialize_lattice(lattice, nrows, ncols); // Randomize the lattice
        run_simulation(lattice, nrows, ncols, nframes, algsteps, J, h, T); // Go baby go
        free(lattice);
    }
    else {
        // Otherwise, ask for the parameters manually
        int nrows, ncols, nframes, algsteps;
        double J, h, T;

        printf("\nShortcut Usage: %s [nrows] [ncols] [nframes] [algsteps] [J] [h] [T]\n\n", argv[0]);
        
        printf("Number of Rows ----------------------> ");
        scanf_s("%d", &nrows);
        
        printf("Number of Columns -------------------> ");
        scanf_s("%d", &ncols);
        
        printf("Number of Frames --------------------> ");
        scanf_s("%d", &nframes);
        
        printf("Number of Iterations Between Frames -> ");
        scanf_s("%d", &algsteps);

        printf("Ferromagnetic Coupling Constant -----> ");
        scanf_s("%lf", &J);

        printf("Magnetic Field Strength -------------> ");
        scanf_s("%lf", &h);

        printf("Temperature -------------------------> ");
        scanf_s("%lf", &T);

        printf("\n\nRunning...\n\n");

        int** lattice = (int**)malloc(nrows * sizeof(int*));
        for (int i = 0; i < nrows; i++) {
            lattice[i] = (int*)malloc(ncols * sizeof(int));
        }

        initialize_lattice(lattice, nrows, ncols); // Randomize the lattice
        run_simulation(lattice, nrows, ncols, nframes, algsteps, J, h, T); // Go baby go
        free(lattice);
    }

    return 0;
}


/*!
\brief Runs a customizable batch script with the intent of converting the pbm 
files into png frames.

\return void
*/
void pbms2images()
{
    system("pbms2images.bat");
}


/*!
\brief Runs a customizable batch script with the intent of converting the 
frames into a proper video. The dimensions of the video are passed to the 
script as well.

@param lattice The 2D grid of spin values
@param nrows  Number of rows
@param ncols  Number of columns

\return void
*/
void images2video(int** lattice, int nrows, int ncols)
{
    char command[0x100];
    snprintf(command, sizeof(command), "images2video.bat %d %d", ncols, nrows);
    system(command);
}


/*!
\brief Writes and saves a pbm file fully describing the state of the lattice at a
particular iteration.

@param lattice  The 2D grid of spin values
@param nrows  Number of rows
@param ncols  Number of columns
@param frame  The index of the frame being saved

\return void
*/
void lattice2pbm(int** lattice,int nrows, int ncols, const int frame)
{
    // Appropriately format the numbered filename
    char f[0x100];                                              
    snprintf(f, sizeof(f), "frames/frame%d.pbm", frame);        
                                                                
    FILE* file;                                                 
    fopen_s(&file, f, "wb");                                    
                                                                
    fprintf(file, "P1\n");                                      
    fprintf(file, "%d %d\n", nrows, ncols);                     
                                                                
    for (int i = 0; i < nrows; i++) {                           
        for (int j = 0; j < ncols; j++) {                       
            fprintf(file, "%d ", (lattice[i][j] == 1 ? 1 : 0)); 
        }                                                       
                                                                
        fprintf(file, "\n");                                    
    }                                                           
                                                                
    fclose(file);                                               
}


/*!
\brief Outputs a quasi-random number from 0.0 to 1.0

\return The quasi-random number
*/
double prob()
{
    return (double)rand() / RAND_MAX;
}


/*!
\brief Calculates the sum of the spins of the neighbors of a specified point

@param lattice  The 2D grid of spin values
@param nrows  Number of rows
@param ncols  Number of columns
@param i  The row in question
@param j  The column in question

\return The resulting sum of spins
*/
int neighbors(int** lattice, int nrows, int ncols, int i, int j)
{
    return lattice[(i + 1) % nrows][j] +
        lattice[i][(j + 1) % ncols] +
        lattice[((i - 1) + nrows) % nrows][j] +
        lattice[i][((j - 1) + ncols) % ncols];
}


/*!
\brief Performs Randomize the Ising lattice

@param lattice  The 2D grid of spin values
@param nrows  Number of rows
@param ncols  Number of columns

\return void
*/
void initialize_lattice(int** lattice, int nrows, int ncols)
{
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++)
        {
            if (prob() > 0.5) {
                lattice[i][j] = 1;
            }
            else {
                lattice[i][j] = -1;
            }
        }
    }
}


/*!
\brief Performs one step of the Metropolis-Hastings Algorithm

Selects a point at random and calculates the energy difference.
If this difference is less than zero, the spin is automatically flipped,
otherwise it's flipped with probability \f$P = e^{-\frac{dE}{k_BT}} \f$

@param lattice  The 2D grid of spin values
@param nrows  Number of rows
@param ncols  Number of columns
@param nframes  The number of frames desired to visualize the system
@param algsteps  The number of algorithm steps between each recorded frame
@param J  Ferromagnetic Coupling Constant
@param h  Magnetic field strength
@param T  Temperature

\return void
*/
void metropolis_hastings_step(int** lattice, int nrows, int ncols, int nframes, int algsteps, double J, double h, double T) {
    // Select a random point in the lattice
    int i = rand() % nrows;
    int j = rand() % ncols;

    // Calculates the change in energy if this spin is flipped
    double dE = 2 * (J * neighbors(lattice, nrows, ncols, i, j) - h) * lattice[i][j];

    // If the system is in a lower energy state afterwards, immediately accept
    if (dE < 0.0) {
        lattice[i][j] *= -1;
    }
    // Otherwise, accept with a probability $P = e^{-\frac{dE}{k_B T}}$
    else if(prob() < exp(-dE / (kB * T) ) ){
        lattice[i][j] *= -1;
    }
}


/*!
\brief Run through iterations, generate files, and compile video

Loops through the total number of algorithm iterations (nframes * algsteps)
and performs the necessary file handling by calling the subsequent functions

@param lattice  The 2D grid of spin values
@param nrows  Number of rows
@param ncols  Number of columns
@param nframes  The number of frames desired to visualize the system
@param algsteps  The number of algorithm steps between each recorded frame
@param J  Ferromagnetic Coupling Constant
@param h  Magnetic field strength
@param T  Temperature
\return void
*/
void run_simulation(int** lattice, int nrows, int ncols, int nframes, int algsteps, double J, double h, double T) {
    // Loop through the desired number of frames
    for (int frame = 0; frame < nframes; frame++) {
        lattice2pbm(lattice, nrows, ncols, frame); // Save the frame as a pbm file
        pbms2images(); // Convert pbm to png

        // Loop through the intermediate algorithm steps
        for (int step = 0; step < algsteps; step++) {
            metropolis_hastings_step(lattice, nrows, ncols, nframes, algsteps, J, h, T);
        }
    }

    images2video(lattice, nrows, ncols);
}
