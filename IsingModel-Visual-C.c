const double k_B = 1.0; // Boltzmann constant
void clean();

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

double prob();
void lattice2image(int**, int, int, int);
void images2video(int, int);
void initialize_lattice(int**, int, int);
int neighbors(int**, int, int, int, int);
void metropolis_hastings_step(int**, int, int, double, double, double);
void run_simulation(int**, int, int, int, int, double, double, double);


double prob() {
    return (double)rand() / RAND_MAX;
}


void lattice2image(int** lattice, int nrows, int ncols, const int frame) {
    /************************************************************\
    | This writes the lattice in the appropriate format for a    |
    | 'pbm' file                                                 |
    \************************************************************/
    //////////////////////////////////////////////////////////////
    char f[0x100];                                              //
    snprintf(f, sizeof(f), "frames/frame%d.pbm", frame);        //
                                                                //
    FILE* file;                                                 //
    fopen_s(&file, f, "wb");                                    //
                                                                //
    fprintf(file, "P1\n");                                      //
    fprintf(file, "%d %d\n", nrows, ncols);                     //
                                                                //
    for (int i = 0; i < nrows; i++) {                           //
        for (int j = 0; j < ncols; j++) {                       //
            fprintf(file, "%d ", (lattice[i][j] == 1 ? 1 : 0)); //
        }                                                       //
                                                                //
        fprintf(file, "\n");                                    //
    }                                                           //
                                                                //
    fclose(file);                                               //
    //////////////////////////////////////////////////////////////

    /************************************************************\
    | This next line of code daisy-chains a few cmd commands:    |
    | - Changes into the 'frames/' directory                     |
    | - Converts any 'pbm' files to 'png' files                  |
    | - Deletes the now unnecessary 'pbm' files                  |
    | - Changes directory back to its original location          |
    \************************************************************/
    system("cd frames && magick mogrify -format png *.pbm && del /Q *.pbm && cd ..");
}


void clean() {
    /*********************************************************\
    | This next line of code daisy-chains a few cmd commands: |
    | - Changes into the 'frames/' directory                  |
    | - Deletes the now unnecessary 'png' files               |
    | - Changes directory back to its original location       |
    \*********************************************************/
    system("cd frames && del /Q *.png && cd ..");
}


void images2video(int nrows, int ncols) {
    // Appropriately format the ffmpeg command
    char command[256];
    sprintf_s(command, "ffmpeg -r 30 -f image2 -s %dx%d -i frames/frame%%d.png -vcodec libx264 -crf 25  -pix_fmt yuv420p movies/movie.mp4", nrows, ncols);
    // Run the above command 
    system(command);
    clean();
}


void initialize_lattice(int** lattice, int nrows, int ncols)
/***********************************************************\
| This function simply loops through the lattice and        |
| randomly assigns either plus one or minus one.            |
\***********************************************************/
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


int neighbors(int** lattice, int nrows, int ncols, int i, int j) {
    return lattice[((i + 1) + nrows) % nrows][j] +
        lattice[i][((j + 1) + ncols) % ncols] +
        lattice[((i - 1) + nrows) % nrows][j] +
        lattice[i][((j - 1) + ncols) % ncols];
}


void metropolis_hastings_step(int** lattice, int nrows, int ncols, double J, double h, double T)
/******************************************************************************\
| This function carries out the core iterative step, utilizing the             |
| Metropolis-Hastings Algorithm and Single-Flip Dynamics                       |
\******************************************************************************/
{
    // Select a random point in the lattice
    int i = rand() % nrows;
    int j = rand() % ncols;

    // Calculates the change in energy if this spin is flipped
    double dE = 2 * (J * neighbors(lattice, nrows, ncols, i, j) - h) * lattice[i][j];

    // If the system is in a lower energy state afterwards, immediately accept
    if (dE < 0.0) {
        lattice[i][j] *= -1;
    }
    // Otherwise, accept with a probability P = e^(-dE/(k_B T))
    else if (prob() < exp(-(double)dE / (k_B * T))) {
        lattice[i][j] *= -1;
    }
}


void run_simulation(int** lattice, int nrows, int ncols, int nframes, int algsteps, double J, double h, double T)
/*****************************************************************************\
| Although this function's name is 'run_simulation', its main job is to       |
| loop through the algorithm steps and perform the file creation/deletion     |
| logistics                                                                   |
\*****************************************************************************/
{
    // Loop through the desired number of frames
    for (int frame = 0; frame < nframes; frame++) {
        lattice2image(lattice, nrows, ncols, frame); // Save the frame

        // Loop through the intermediate algorithm steps
        for (int step = 0; step < algsteps; step++) {
            metropolis_hastings_step(lattice, nrows, ncols, J, h, T); // Step
        }
    }

    system("del /Q movies/movie.mp4");

    images2video(nrows, ncols); // Convert the frames into a video using ffmpeg
    clean(); // Deletes the now obsolete images to save space
}


int main(int argc, const char* argv[])
{
    // Check the number of parameters
    if (argc == 8) {
        // Convert commandline arguments from strings to integers
        char** endptr = NULL;
        int nrows = strtol(argv[1], endptr, 0);
        int ncols = strtol(argv[2], endptr, 0);
        int nframes = strtol(argv[3], endptr, 0);
        int algsteps = strtol(argv[4], endptr, 0);
        double J = strtod(argv[5], endptr);
        double h = strtod(argv[6], endptr);
        double T = strtod(argv[7], endptr);

        int** lattice = (int**)malloc(nrows * sizeof(int*));
        for (int i = 0; i < nrows; i++) {
            lattice[i] = (int*)malloc(ncols * sizeof(int));
        }

        initialize_lattice(lattice, nrows, ncols); // Randomize the lattice
        run_simulation(lattice, nrows, ncols, nframes, algsteps, J, h, T); // Go baby go
        free(lattice);
    }
    else {
        // Print out a helpful message to remind you of the proper usage
        printf("Usage: %s [nrows] [ncols] [Number of Frames] [Algorithm Steps Per Frame] [Ferromagnetic Coupling] [Magnetic Field] [Temperature]\n", argv[0]);
    }

    return 0;
}
