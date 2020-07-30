///\headerfile random_generators.h
///\author Ethan Knox
///\date 7/22/2020.

#ifndef ISINGMODEL_VISUAL_RANDOM_GENERATORS_H
#define ISINGMODEL_VISUAL_RANDOM_GENERATORS_H

#include <random>

///\brief Reusable uniform random double function
///
///Generates a uniformly distributed random double between min and max.
///
///\param min
///\param max
///\return uniform random double
inline double uniformfloating(double max)
{
    static std::mt19937 mt{std::random_device{}()};
    static std::uniform_real_distribution<double> dist;
    using pick = std::uniform_real_distribution<double>::param_type;

    return dist(mt, pick((double_t)0.0, max));
}

///\brief Reusable uniform random integer function
///
///Generates a uniformly distributed random integer between min and max.
///
///\param min
///\param max
///\return uniform random integer
inline int uniformintegral(int max)
{
    static std::mt19937 mt{std::random_device{}()};
    static std::uniform_int_distribution<int> dist;
    using pick = std::uniform_int_distribution<int>::param_type;

    return dist(mt, pick(0, max - 1));
}

#endif //ISINGMODEL_VISUAL_RANDOM_GENERATORS_H
