//
// Created by ethan on 7/24/2020.
//

#include "../include/wolff_step.h"

void wolff_step(Lattice &lattice, double T) {
    double p  = 1.0 - exp(-2.0 / T);
    int j, j_idx;
    std::vector<int> Pocket;
    Pocket.reserve(lattice.rows*lattice.cols);
    std::vector<int> Cluster;
    Cluster.reserve(lattice.rows*lattice.cols);

    int k = uniformintegral(0, lattice.rows*lattice.cols - 1);
    Pocket.push_back(k);
    Cluster.push_back(k);
    while(!Pocket.empty()){
        j_idx = uniformintegral(0,Pocket.size()-1);
        j = Pocket[j_idx];
        for(auto l : lattice.neighbors(j/lattice.rows,j%lattice.rows)){
            if(lattice(l) == lattice(j) && !std::count(Cluster.begin(), Cluster.end(),l) && uniformfloating(0.0, 1.0) < p){
                Pocket.push_back(l);
                Cluster.push_back(l);
            }
        }
        Pocket.erase(Pocket.begin()+j_idx);
    }
    for(auto s: Cluster){
        lattice.flip(s);
    }
}
