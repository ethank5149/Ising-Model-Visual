///\headerfile random_generators.h
///\author Ethan Knox
///\date 7/22/2020.

#ifndef ISINGMODEL_VISUAL_RANDOM_GENERATORS_H
#define ISINGMODEL_VISUAL_RANDOM_GENERATORS_H

#include <random>

/// \brief Reusable uniform random double function
///
/// Generates a uniformly distributed random double between min and max.
///
/// \param min
/// \param max
/// \return uniform random double
inline double uniform(double min, double max)
{
    // use thread_local to make this function thread safe
    thread_local static std::mt19937 mt{std::random_device{}()};
    thread_local static std::uniform_real_distribution<double> dist;
    using pick = std::uniform_real_distribution<double>::param_type;

    return dist(mt, pick(min, max));
}

/// \brief Reusable uniform random integer function
///
/// Generates a uniformly distributed random integer between min and max.
///
/// \param min
/// \param max
/// \return uniform random integer
inline int randint(int min, int max)
{
    // use thread_local to make this function thread safe
    thread_local static std::mt19937 mt{std::random_device{}()};
    thread_local static std::uniform_int_distribution<int> dist;
    using pick = std::uniform_int_distribution<int>::param_type;

    return dist(mt, pick(min, max));
}

/// \brief Reusable uniform random integer function
///
/// Generates a uniformly distributed random integer between min and max.
///
/// \param min
/// \param max
/// \return uniform random integer
inline int uniformintegral(int min, int max)
{
    // use thread_local to make this function thread safe
    thread_local static std::mt19937 mt{std::random_device{}()};
    thread_local static std::uniform_int_distribution<int> dist;
    using pick = std::uniform_int_distribution<int>::param_type;

    return dist(mt, pick(min, max));
}

/// \brief Reusable uniform random double function
///
/// Generates a uniformly distributed random double between min and max.
///
/// \param min
/// \param max
/// \return uniform random double
inline double uniformfloating(double min, double max)
{
    // use thread_local to make this function thread safe
    thread_local static std::mt19937 mt{std::random_device{}()};
    thread_local static std::uniform_real_distribution<double> dist;
    using pick = std::uniform_real_distribution<double>::param_type;

    return dist(mt, pick(min, max));
}

#endif //ISINGMODEL_VISUAL_RANDOM_GENERATORS_H
