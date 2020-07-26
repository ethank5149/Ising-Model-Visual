//
// Created by ethan on 7/26/2020.
//

#ifndef ISINGMODEL_VISUAL_LATTICE_H
#define ISINGMODEL_VISUAL_LATTICE_H

#include <cstdlib>
#include <cstdint>
#include <vector>


template<typename class_integral_type_1, typename class_integral_type_2>
class Lattice {
public:
    class_integral_type_1 nrows{};
    class_integral_type_2 ncols{};
    char method{};

    int* lattice;

    std::vector<std::size_t> cluster{};
    std::vector<std::size_t> perimeter{};

    template<typename integral_type_1, typename integral_type_2>
    Lattice(integral_type_1 input_nrows, integral_type_2 input_ncols, char input_method) {
        nrows = input_nrows;
        ncols = input_ncols;
        method = input_method;

        lattice = (int*)malloc(nrows*ncols * sizeof(int));

        if(method == 'W'){ // We only need this if the Wolff algorithm was chosen
            perimeter.reserve(4 * nrows * ncols);
            cluster.reserve(nrows * ncols);
        }
    }
};


#endif //ISINGMODEL_VISUAL_LATTICE_H