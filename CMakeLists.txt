# CMakeList.txt : CMake project for IsingModel-Visual, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("IsingModel-Visual")

# Add source to this project's executable.
add_executable (IsingModel-Visual 
"src/IsingModel-Visual.cpp" src/file_management.cpp include/file_management.h include/ising_struct.h src/lattice2pbm.cpp include/lattice2pbm.h src/metropolis_hastings_neighbors.cpp include/metropolis_hastings_neighbors.h src/pbm2png.cpp include/pbm2png.h src/pngs2video.cpp include/pngs2video.h src/randomize_lattice.cpp include/randomize_lattice.h src/metropolis_hastings_step.cpp include/metropolis_hastings_step.h src/run_simulation.cpp include/run_simulation.h include/random_generators.h)

# TODO: Add tests and install targets if needed.
