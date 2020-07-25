//
// Created by ethan on 7/24/2020.
//

#include "../include/wolff_step.h"
#include <utility>
#include <iostream>

void wolff_step(int** lattice, Ising_Params &p) {
    double P  = 1.0 - exp(-2.0*p.J / p.T);
    std::pair<int, int> chosen;
    std::vector<std::pair<int, int>> cluster;
    cluster.reserve(p.nrows*p.ncols);

    std::vector<std::pair<int, int>> perimeter;
    perimeter.reserve(p.nrows*p.ncols);

    std::vector<std::pair<int, int>> neighbors(4);

    int seed_i = randint(0, p.nrows);
    int seed_j = randint(0, p.ncols);

    cluster.emplace_back(seed_i, seed_j);//We accept this flip with probability 1
    perimeter.emplace_back(seed_i, seed_j);//Seed the perimeter list

    while(!perimeter.empty()){
        chosen = perimeter.front();//Pick a spin from the perimeter list

        neighbors = wolff_neighbors(p.nrows, p.ncols, chosen.first, chosen.second);

        for(std::pair<int, int> spin : neighbors){
            if(lattice[spin.first][spin.second] == lattice[seed_i][seed_j] && // If the spin is parallel with the seed
                    !std::count(cluster.begin(), cluster.end(),spin) && //If the spin isn't already in the cluster
               uniform(0.0, 1.0) < P){//If probability < P

                perimeter.push_back(spin);
                cluster.push_back(spin);
            }
        }

        perimeter.erase(perimeter.begin());
    }

    for(auto s: cluster){
        lattice[s.first][s.second] *= -1;
    }
}
