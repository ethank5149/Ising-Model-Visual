#include <cstdio>
#include <string>
#include <boost/filesystem/fstream.hpp>
#include <boost/program_options.hpp>
namespace opt = boost::program_options;

#include "../include/Ising_Params.h"
#include "../include/run_simulation.h"

int main(int argc, const char* argv[])
{
    long nrows, ncols, stopiter, framestep;
    double J, h, T;
    char method, geometry;

    opt::options_description params("Simulation Parameters");

    params.add_options()
            ("help,h", "print usage message")
            ("nrows,r", opt::value<long>(&nrows)->default_value(500), "Number of rows")
            ("ncols,c", opt::value<long>(&ncols)->default_value(500), "Number of columns")
            ("stopiter,s", opt::value<long>(&stopiter)->default_value(250000), "Number of iterations")
            ("framestep,f", opt::value<long>(&framestep)->default_value(2500), "Number of iterations between frames")
            ("J,j", opt::value<double>(&J)->default_value(1.0), "Ferromagnetic Coupling Constant")
            ("h,h", opt::value<double>(&h)->default_value(0.0), "Magnetic Field Strength")
            ("T,t", opt::value<double>(&T)->default_value(1.8), "Temperature")
            ("method,m", opt::value<char>(&method)->default_value('M'), "Solution Method")
            ("geometry,g", opt::value<char>(&geometry)->default_value('S'), "Grid Geometry")
            ;

    opt::variables_map vm;

    try { opt::store(opt::parse_command_line(argc, argv, params), vm); }
    catch (const opt::reading_file& e) { std::cout << "Error: " << e.what() << std::endl; }

    if(argc == 2){
        if (vm.count("help")) {
            std::cout << params << std::endl;
            return 1;
        }
        else{
            try { opt::store(opt::parse_config_file<char>(argv[1], params), vm); }
            catch (const opt::reading_file& e) { std::cout << "Error: " << e.what() << std::endl; }
        }
    }

    opt::notify(vm);

    printf("\n2D ISING MODEL - VISUAL SIMULATION\n");
    printf(  "----------------------------------\n");

    Ising_Params p = Ising_Params(nrows, ncols, stopiter, framestep, J, h, T, method, geometry);

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
