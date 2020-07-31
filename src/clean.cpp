//
// Created by ethan on 7/30/2020.
//

#include "../include/clean.h"
#include <vector>
#include <iostream>

void clean_pngs(Ising &p){
    std::cout << "\nCleaning up leftover frames... ";

    std::vector<boost::filesystem::path> paths;
    for(const auto &entry : boost::filesystem::recursive_directory_iterator(p.outputdir)) {
        if (entry.path().extension() == ".png") {
            paths.emplace_back(entry.path());
        }
    }

    for(const auto &path : paths){
        boost::filesystem::remove(path);
    }

    std::cout << "Done!\n" << std::endl;
}

void clean_all(Ising &p){
    std::cout << "\nCleaning up leftover files... ";

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

    std::cout << "Done!\n" << std::endl;
}