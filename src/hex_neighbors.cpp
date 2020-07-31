///\file hex_neighbors.cpp
///\author Ethan Knox
///\date 7/27/2020.

#include "../include/hex_neighbors.h"

///\brief Return the indices of a point's neighbors
///
///Returns a vector containing the flattened indices of its neighbors in a hexagonal grid
///
///\param rows  The number of rows in the grid
///\param cols  The number of columns in the grid
///\param idx  The index in question
///
///\return std::<vector> containing the neighbors' indices
std::vector<long> hex_neighbors(long rows, long cols, long idx) {
    return std::vector<long>{((idx % rows) + 1 + rows) % rows + rows * (((idx / rows) + 0 + cols) % cols),
                             ((idx % rows) + 0 + rows) % rows + rows * (((idx / rows) + 1 + cols) % cols),
                             ((idx % rows) - 1 + rows) % rows + rows * (((idx / rows) + 0 + cols) % cols),
                             ((idx % rows) + 0 + rows) % rows + rows * (((idx / rows) - 1 + cols) % cols),
                             ((idx % rows) + 1 + rows) % rows + rows * (((idx / rows) + 1 + cols) % cols),
                             ((idx % rows) - 1 + rows) % rows + rows * (((idx / rows) - 1 + cols) % cols),
                             ((idx % rows) + 1 + rows) % rows + rows * (((idx / rows) - 1 + cols) % cols),
                             ((idx % rows) - 0 + rows) % rows + rows * (((idx / rows) + 1 + cols) % cols)};
}