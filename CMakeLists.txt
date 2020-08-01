# CMakeList.txt : CMake project for IsingModel-Visual, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# Unnecessary in VS
#set(CMAKE_TOOLCHAIN_FILE "/vcpkg/scripts/buildsystems/vcpkg.cmake")

project ("IsingModel-Visual")

# Add source to this project's executable.
add_executable (IsingModel-Visual
        src/IsingModel-Visual.cpp
        src/lattice2png.cpp include/lattice2png.h
        src/pngs2video.cpp include/pngs2video.h
        src/metropolis_hastings_step.cpp include/metropolis_hastings_step.h
        src/run_simulation.cpp include/run_simulation.h
        include/random_generators.h
        src/Ising.cpp include/Ising.h
        src/wolff_step.cpp include/wolff_step.h
        src/sqr_neighbors.cpp include/sqr_neighbors.h
        src/hex_neighbors.cpp include/hex_neighbors.h 
        src/clean.cpp include/clean.h)


find_package(fmt CONFIG REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS filesystem program_options thread REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(IsingModel-Visual ${Boost_LIBRARIES} fmt::fmt fmt::fmt-header-only)