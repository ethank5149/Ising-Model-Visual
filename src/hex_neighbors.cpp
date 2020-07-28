///\file hex_neighbors.cpp
///\author Ethan Knox
///\date 7/27/2020.

#include "../include/hex_neighbors.h"

/// \brief Return a vector of the indices of a point's neighbors
///
///
///
///
/// \param p  An instance of Ising_Params
/// \param idx  The index in question
///
/// \return Vector of neighbor indices
std::vector<long> hex_neighbors(long rows, long cols, long idx) {
    return std::vector<long>{
            cols * ((idx / rows + 1 + rows) % rows) + ((idx % cols) + 0 + cols) % cols,
            cols * ((idx / rows + 0 + rows) % rows) + ((idx % cols) + 1 + cols) % cols,
            cols * ((idx / rows - 1 + rows) % rows) + ((idx % cols) + 0 + cols) % cols,
            cols * ((idx / rows + 0 + rows) % rows) + ((idx % cols) - 1 + cols) % cols,
            cols * ((idx / rows + 1 + rows) % rows) + ((idx % cols) + 1 + cols) % cols,
            cols * ((idx / rows - 1 + rows) % rows) + ((idx % cols) - 1 + cols) % cols,
            cols * ((idx / rows - 1 + rows) % rows) + ((idx % cols) + 1 + cols) % cols,
            cols * ((idx / rows + 1 + rows) % rows) + ((idx % cols) - 1 + cols) % cols};
}