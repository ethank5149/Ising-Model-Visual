# CMakeList.txt : CMake project for IsingModel-Visual, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("IsingModel-Visual")

# Add source to this project's executable.
add_executable (IsingModel-Visual 
"src/IsingModel-Visual.cpp" src/file_management.cpp include/file_management.h include/ising_struct.h)

# TODO: Add tests and install targets if needed.
