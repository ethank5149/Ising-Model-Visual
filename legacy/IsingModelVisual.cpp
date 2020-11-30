#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>
#include <string>

using namespace std;

const float J = 1.;
const float kB = 1.;

random_device rd;
mt19937 rng(rd());
uniform_real_distribution<float> standard_uniform(0., 1.);

int main(int argc, char** argv) 
{ 

    if(argc != 7){
        cout << "Usage: ./IsingModelVisual [nrows] [ncols] [T] [H] [ncaptures] [speed]" << endl;
        return(0);
    }
    else{
        int number_of_rows = atoi(argv[1]);
        int number_of_cols = atoi(argv[2]);
        float T = atof(argv[3]);
        float H = atof(argv[4]);
        int number_of_captures = atoi(argv[5]);
        float speed = atof(argv[6]);

        int i, j, neighbors;
        float chance, dE, probability, percentage;
        ofstream outfile;

        int iterations_per_capture = (int)(speed * number_of_rows * number_of_cols);
        int iterations           = iterations_per_capture * number_of_captures;

        vector<int> row(number_of_cols, 0);
        vector<vector<int>> grid(number_of_rows, row);

        uniform_int_distribution<int> random_row(0, number_of_rows - 1);
        uniform_int_distribution<int> random_col(0, number_of_cols - 1);

        // Randomize the Grid
        for(size_t i = 0; i < number_of_rows; i++){
            for(size_t j = 0; j < number_of_cols; j++){
                grid.at(i).at(j) = standard_uniform(rng) < 0.5 ? 1 : -1;
            }
        }
        
        outfile.open("results.dat", ios::out);
        outfile << "# captures=" << number_of_captures << ", Rows=" << number_of_rows << ", Cols=" << number_of_cols << ", T=" << T << ", H=" << H << endl;
        
        // For each capture
        for(size_t t = 0; t < number_of_captures; t++){
            percentage = 100.0 * t / number_of_captures;
            cout << "\r Running: " << setw(3) << static_cast<int>(percentage) << "% " << flush;
            
            // Iterate the desired number of times
            for(size_t iter = 0; iter < iterations; iter++){
                i = random_row(rng); j = random_col(rng);  // Pick a random point on the grid
                chance = standard_uniform(rng);  // Might as well precalculate this too
                
                // Calculate the neighbors for this specific spin
                neighbors = grid.at( (i + 1)                   % number_of_rows).at(  j                                        ) + 
                            grid.at(((i - 1) + number_of_rows) % number_of_rows).at(  j                                        ) + 
                            grid.at(  i                                        ).at( (j + 1)                   % number_of_cols) + 
                            grid.at(  i                                        ).at(((j - 1) + number_of_cols) % number_of_cols);
                // Perform the spin flip algorithm
                dE = 2. * (J * neighbors - H) * grid.at(i).at(j);
                probability = dE < 0. ? 1. : exp(-dE / (kB * T));
                if(chance < probability){
                    grid.at(i).at(j) = -grid.at(i).at(j);
                }
            }
            
            // Write data to file
            for(size_t i = 0; i < number_of_rows; i++){
                for(size_t j = 0; j < number_of_cols; j++){
                    outfile << grid.at(i).at(j) << " ";
                }
            }
            outfile << endl;
            
            percentage = 100.0 * t / number_of_captures;
            cout << "\r Running: " << setw(3) << static_cast<int>(percentage + 1) << "% " << flush;
            
        }
        outfile.close();
        cout << endl << endl;
    }
    return 0;
}