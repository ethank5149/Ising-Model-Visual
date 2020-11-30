///\file clean.cpp
///\author Ethan Knox
///\date 7/30/2020.

#include "../include/clean.h"
#include <vector>
#include <iostream>

///\brief Removes all existing png photos from the output directory
///
///All '.png' files are deleted.
///\todo Enable the ability to save raw frames
///
///\param p  Instance of the Ising class
///
///\return void
void clean_pngs(Ising &p){
    std::cout << "Cleaning up leftover frames... ";

    std::vector<boost::filesystem::path> paths;
    for(const auto &entry : boost::filesystem::recursive_directory_iterator(p.outputdir)) {
        if (entry.path().extension() == ".png") {
            paths.emplace_back(entry.path());
        }
    }

    for(const auto &path : paths){
        boost::filesystem::remove(path);
    }

    std::cout << "Done!" << std::endl;
}

///\brief Removes all (un-renamed) output files from the output directory
///
///All '.png' files are deleted, as well as any previously existing
///'output.mp4' and 'output.gif' files.
///\todo Enable the ability to save raw frames
///
///\param p an instance of the Ising class
///
///\return void
void clean_all(Ising &p){
    std::cout << "Cleaning up leftover files... ";

    std::vector<boost::filesystem::path> paths;
    for(const auto &entry : boost::filesystem::recursive_directory_iterator(p.outputdir)) {
        if (entry.path().extension() == ".png") {
            paths.emplace_back(entry.path());
        }
    }

    for(const auto &path : paths){
        boost::filesystem::remove(path);
    }

    boost::filesystem::remove(p.outputdir/"output.mp4");
    boost::filesystem::remove(p.outputdir/"output.gif");

    std::cout << "Done!" << std::endl;
}