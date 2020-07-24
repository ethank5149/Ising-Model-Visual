//
// Created by ethan on 7/24/2020.
//

#include "../include/Lattice.h"

Lattice::Lattice(int r, int c) {
    _rows = r;
    _cols = c;
    rows = _rows;
    cols = _cols;
    _spins = (int *) malloc(rows * cols * sizeof(int));
}

int Lattice::operator()(int i) {
    return _spins[i];
}

int Lattice::operator()(int i, int j) {
    return _spins[i + _cols * j];
}

void Lattice::flip(int i) {
    _spins[i] *= -1;
}

void Lattice::flip(int i, int j) {
    _spins[i + _cols * j] *= -1;
}

void Lattice::randomize() {
    for(int i = 0; i < _rows; i++){
        for(int j = 0; j < _cols;  j++){
            _spins[i + _cols * j] = 2*uniformintegral(0,1)-1;
        }
    }

}


