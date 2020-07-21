#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "sys/stat.h"

#include "include/metropolis_hastings_neighbors.h"

/*!
\def kB
\brief Boltzmann constant
*/
#define kB 1.0

// Function Declarations
void pngs2video();
void lattice2png(int**, int, int, int);
double prob();
void initialize_lattice(int**, int, int);
void metropolis_hastings_step(int**, int, int, double, double, double);
void run_simulation(int**, int, int, int, int, int, double, double, double);

int main(int argc, const char* argv[])
{
    int nrows, ncols, startiter, stopiter, framestep;
    double J, h, T;

    time_t t;
    srand((unsigned)time(&t));

    printf("\n2D ISING MODEL - VISUAL SIMULATION\n");
    printf(  "----------------------------------\n\n");

    // Check the number of parameters to enable shortcut usage
    if (argc == 2) {
        printf("Getting Parameters From File...\n");

        FILE* file;
        fopen_s(&file, argv[1], "r");

        fscanf_s(file, "%*s %*s %d", &nrows);
        fscanf_s(file, "%*s %*s %d", &ncols);
        fscanf_s(file, "%*s %*s %d", &startiter);
        fscanf_s(file, "%*s %*s %d", &stopiter);
        fscanf_s(file, "%*s %*s %d", &framestep);
        fscanf_s(file, "%*s %*s %lf", &J);
        fscanf_s(file, "%*s %*s %lf", &h);
        fscanf_s(file, "%*s %*s %lf", &T);

        fclose(file);
        printf("Done!\n\n");
    }

    else if (argc == 9) {
        // Convert commandline arguments from strings
        char** endptr = NULL;
        nrows = strtol(argv[1], endptr, 0);
        ncols = strtol(argv[2], endptr, 0);
        startiter = strtol(argv[3], endptr, 0);
        stopiter = strtol(argv[4], endptr, 0);
        framestep = strtol(argv[5], endptr, 0);
        J = strtod(argv[6], endptr);
        h = strtod(argv[7], endptr);
        T = strtod(argv[8], endptr);
    }
    else {
        printf("\nShortcut Usage: %s [nrows] [ncols] [startiter] [stopiter] [framestep] [J] [h] [T]\n\n", argv[0]);
        
        printf("Number of Rows ------------------> ");
        scanf_s("%d", &nrows);
        
        printf("Number of Columns ---------------> ");
        scanf_s("%d", &ncols);
        
        printf("Starting Iteration --------------> ");
        scanf_s("%d", &startiter);

        printf("Stopping Iteration --------------> ");
        scanf_s("%d", &stopiter);
        
        printf("Iterations Between Frames -------> ");
        scanf_s("%d", &framestep);

        printf("Ferromagnetic Coupling Constant -> ");
        scanf_s("%lf", &J);

        printf("Magnetic Field Strength ---------> ");
        scanf_s("%lf", &h);

        printf("Temperature ---------------------> ");
        scanf_s("%lf", &T);
    }

    printf("Parameters:\n");
    printf("nrows, ncols = %d, %d\n", nrows, ncols);
    printf("startiter, stopiter, framestep = %d, %d, %d\n", startiter, stopiter, framestep);
    printf("J, h, T = %f, %f, %f\n\n", J, h, T);

    printf("Running...\n");

    int** lattice = (int**)malloc(nrows * sizeof(int*));
    for (int i = 0; i < nrows; i++) {
        lattice[i] = (int*)malloc(ncols * sizeof(int));
    }

    initialize_lattice(lattice, nrows, ncols); // Randomize the lattice
    run_simulation(lattice, nrows, ncols, startiter, stopiter, framestep, J, h, T); // Go baby go
    free(lattice);

    printf("Done!\n");
    printf("----------------------------------\n");


    return 0;
}


int exists(const char* fname)
{
    struct stat buffer;
    int exist = stat(fname, &buffer);
    if (exist == 0)
        return 1;
    else // -1
        return 0;
}


void clean() {
    if(exists("frame0.pbm")) {
        system("del /Q *.pbm");
    }
    if (exists("frame0.png")) {
        system("del /Q *.png");
    }

    if (exists("output.mp4")) {
        system("del /Q output.mp4");
    }
}


/*!
\brief Runs a customizable batch script with the intent of converting the 
frames into a proper video. The dimensions of the video are passed to the 
script as well.

\return void
*/
void pngs2video()
{
    system("ffmpeg -nostats -loglevel 0 -i frame%d.png output.mp4 && del /Q *.png");
    if (exists("output.mp4")) {
        system("ffmpeg -nostats -loglevel 0 -i output.mp4 output.gif");
    }
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
void lattice2png(int** lattice,int nrows, int ncols, const int frame)
{
    // Appropriately format the numbered filename
    char savefile[0x100];         
    char convertcommand[0x100];
    snprintf(savefile, sizeof(savefile), "frame%d.pbm", frame); // Save file as a pbm
    snprintf(convertcommand, sizeof(convertcommand), 
        "ffmpeg -nostats -loglevel 0 -i frame%d.pbm frame%d.png && del /Q frame%d.pbm", 
        frame, frame, frame); // Immediately convert into a png and delete the pbm to save space
                                                                
    FILE* file;                                                 
    fopen_s(&file, savefile, "wb");                                    

    fprintf(file, "P1\n");                                      
    fprintf(file, "%d %d\n", nrows, ncols);                     
                                                                
    for (int i = 0; i < nrows; i++) {                           
        for (int j = 0; j < ncols; j++) {                       
            fprintf(file, "%d ", (lattice[i][j] == 1 ? 1 : 0)); 
        }                                                                                                             
        fprintf(file, "\n");                                    
    }                                                                                                  
    
    fclose(file);        
    system(convertcommand);
}


/*!
\brief Outputs a quasi-random number from 0.0 to 1.0

\return The quasi-random number
*/
double prob()
{
    return (double)rand() / RAND_MAX;
}


///*!
//\brief Calculates the sum of the spins of the neighbors of a specified point
//
//@param lattice  The 2D grid of spin values
//@param nrows  Number of rows
//@param ncols  Number of columns
//@param i  The row in question
//@param j  The column in question
//
//\return The resulting sum of spins
//*/
//int neighbors(int** lattice, int nrows, int ncols, int i, int j)
//{
//    return lattice[(i + 1) % nrows][j] +
//        lattice[i][(j + 1) % ncols] +
//        lattice[((i - 1) + nrows) % nrows][j] +
//        lattice[i][((j - 1) + ncols) % ncols];
//}


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
void metropolis_hastings_step(int** lattice, int nrows, int ncols, double J, double h, double T) {
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
void run_simulation(int** lattice, int nrows, int ncols, int startiter, int stopiter, int framestep, double J, double h, double T) {
    _mkdir("output");
    chdir("output");

    const char method = "metropolis";
    void (*step)(int** lattice, int nrows, int ncols, double J, double h, double T) = &metropolis_hastings_step;

    //if (method == "metropolis") {
    //    *step = &metropolis_hastings_step;
    //}

    clean();
    // Loop through the desired number of frames
    for (int iter = 0; iter < stopiter; iter++) {
        if(iter >= startiter && (iter - startiter) % framestep == 0){
            lattice2png(lattice, nrows, ncols, (iter - startiter) / framestep); // Save the frame as a png
        }

        step(lattice, nrows, ncols, J, h, T);
    }

    pngs2video();
}
