#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <boost/program_options.hpp>
#include "IsingModel.h"

namespace opt = boost::program_options;

int main(int argc, char** argv) {
    int rows, cols, nT, nH, nR, nS, frames, skip;
    double Ti, Tf, Hi, Hf, J, mu, kB;
    bool sim, vid;

    opt::options_description params("Ising Model Parameters");

    params.add_options()
        ("help,h", "show usage")
        ("rows,r", opt::value< int >(&rows)->default_value(15), "number of rows")
        ("cols,c", opt::value< int >(&cols)->default_value(15), "number of columns")
        ("nR", opt::value< int >(&nR)->default_value(1000), "number of relaxation steps")
        ("nS", opt::value< int >(&nS)->default_value(1000), "sample size")
        ("Ti,i", opt::value<double>(&Ti)->default_value(1.5), "initial temperature")
        ("Tf", opt::value<double>(&Tf)->default_value(3.5), "final temperature")
        ("Hi", opt::value<double>(&Hi)->default_value(0.), "initial magnetic field")
        ("Hf", opt::value<double>(&Hf)->default_value(1.), "final magnetic field")
        ("nT,n", opt::value< int >(&nT)->default_value(1000), "number of time steps")
        ("nH", opt::value< int >(&nH)->default_value(1), "number of magnetic field steps")
        ("frames,f", opt::value< int >(&frames)->default_value(1000), "number of frames")
        ("skip,s", opt::value< int >(&skip)->default_value(1), "number of updates between frames")
        ("J", opt::value<double>(&J)->default_value(1.), "ferromagnetic coupling constant")
        ("kB", opt::value<double>(&kB)->default_value(1.), "Boltzmann's constant")
        ("mu", opt::value<double>(&mu)->default_value(1.), "magnetic moment")
        ("vid", opt::value<bool>(&vid)->default_value(true), "create a visualization of the relaxation algorithm")
        ("sim", opt::value<bool>(&sim)->default_value(true), "run simulation and save results to a compressed numpy (npz) file")
        ;

    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc, argv, params), vm);

    if (vm.count("help")) {
        std::cout << params << std::endl;
        return 1;
    }
    else {
        opt::notify(vm);

        std::cout << "\n2D Ising Model Simulation" << std::endl;
        std::cout << "=========================" << std::endl;

        if (sim) { // sim and vid are mutually exclusive, with sim taking precedence

            std::cout << "Running Simulation:" << std::endl;
            IsingModel ising(rows, cols);
            ising.simulate(Ti, Tf, nT, Hi, Hf, nH, nR, nS);

        }
        else {
            std::cout << "Creating Visualization:" << std::endl;
            IsingModel ising(rows, cols);
            ising.visualize(frames, skip, Ti, Hi);
        }

        std::cout << "\n\nDone!" << std::endl;
        std::cout << "=========================" << std::endl;
        return 0;
    }
}