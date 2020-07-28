# CMakeList.txt : CMake project for IsingModel-Visual, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project ("IsingModel-Visual")

# Add source to this project's executable.
add_executable (IsingModel-Visual "src/IsingModel-Visual.cpp"
        src/lattice2png.cpp include/lattice2png.h
        src/pngs2video.cpp include/pngs2video.h
        src/metropolis_hastings_step.cpp include/metropolis_hastings_step.h
        src/run_simulation.cpp include/run_simulation.h
        include/random_generators.h src/Ising_Params.cpp include/Ising_Params.h src/wolff_step.cpp include/wolff_step.h src/sqr_neighbors.cpp include/sqr_neighbors.h src/hex_neighbors.cpp include/hex_neighbors.h)

