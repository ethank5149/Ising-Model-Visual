///\file wolff_neighbors.cpp
///\author Ethan Knox
///\date 7/24/2020.

#include "../include/wolff_neighbors.h"

/// \brief Returns the pairs of indexes making up the point's neighbors
///
/// \param nrows  Number of rows
/// \param ncols  Number of columns
/// \param i  The row in question
/// \param j  The column in question
///
/// \return The vector of index pairs
std::vector<std::pair<int, int>> wolff_neighbors(int nrows, int ncols, int i, int j)
{
    std::vector<std::pair<int, int>> neighbors {std::make_pair((i + 1) % nrows,j),
                                          std::make_pair(i,(j + 1) % ncols),
                                          std::make_pair(((i - 1) + nrows) % nrows,j),
                                          std::make_pair(i,((j - 1) + ncols) % ncols)};
    return neighbors;
}