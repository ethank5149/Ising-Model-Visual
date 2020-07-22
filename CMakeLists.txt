# CMakeList.txt : CMake project for IsingModel-Visual, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("IsingModel-Visual")

# Add source to this project's executable.
add_executable (IsingModel-Visual "IsingModel-Visual.cpp" "IsingModel-Visual.h" "metropolis_hastings_neighbors.cpp" "metropolis_hastings_neighbors.h" "metropolis_hastings_step.cpp" "metropolis_hastings_step.h" "ising_struct.h")

# TODO: Add tests and install targets if needed.
