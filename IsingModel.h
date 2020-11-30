#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iomanip>
#include <random>
#include "fmt/format.h"
#include "xtensor/xarray.hpp"
#include "xtensor/xrandom.hpp"
#include "xtensor-io/xnpz.hpp"
#include "xtensor-io/ximage.hpp"


class IsingModel
{
public:
    const double J = 1.;  //Ferromagnetic Coupling Constant
    const double kB = 1.;  //Boltzmann Constant
    const double mu = 1.;  // Magnetic Moment
    const int numvars = 6;
    int rows, cols, size;
    double Tc;

    std::mt19937 rng;
    std::uniform_real_distribution<double> uniform;
    std::uniform_int_distribution<int> row_pmf;
    std::uniform_int_distribution<int> col_pmf;

    xt::xtensor<int, 2> grid{};

    IsingModel(int rows_in, int cols_in) {
        rows = rows_in;
        cols = cols_in;
        size = rows * cols;
        Tc = 2. * J / (kB * (std::log(1. + std::sqrt(2.))));
        row_pmf = std::uniform_int_distribution<int>(0, rows - 1);
        col_pmf = std::uniform_int_distribution<int>(0, cols - 1);
        grid = 2 * xt::random::randint<int>({ rows, cols }, 0, 2) - 1;
    }


    void relax(int n, double t, double h) {
        for (size_t i = 0; i < n; i++) {
            update(t, h);
        }
    }


    void reset() {
        grid = 2 * xt::random::randint<int>({ rows, cols }, 0, 2) - 1;
    }


    int metric_at(int i, int j) {
        return grid((i + 1) % rows, j) + grid((i - 1 + rows) % rows, j) + grid(i, (j + 1) % cols) + grid(i, (j - 1 + cols) % cols);
    }


    xt::xtensor<int, 2> metric() {
        return xt::roll(grid, -1, 0) + xt::roll(grid, 1, 0) + xt::roll(grid, -1, 1) + xt::roll(grid, 1, 1);
    }


    void update(double t, double h) {
        for (size_t obs = 0; obs < size; obs++) {
            int i = row_pmf(rng);
            int j = col_pmf(rng);
            double dE = 2. * (J * metric_at(i, j) - h) * grid(i, j);
            double probability = dE < 0. ? 1. : std::exp(-dE / (kB * t));
            if (uniform(rng) < probability) {
                grid(i, j) = -grid(i, j);
            }
        }
    }


    void simulate(double T_initial, double T_final, int num_T, double h_initial, double h_final, int num_h, int num_R, int num_S) {
        int line;
        int num_obs = num_T * num_h;
        double t, h;
        xt::xtensor<double, 2> dE;

        xt::xtensor<double, 2> results = xt::zeros<double>({ num_obs, numvars });
        xt::xtensor<double, 1> Trange = xt::linspace<double>(T_initial, T_final, num_T);
        xt::xtensor<double, 1> Hrange = xt::linspace<double>(h_initial, h_final, num_h);
        xt::xtensor<double, 1> Esample = xt::zeros<double>({ num_S });
        xt::xtensor<double, 1> Msample = xt::zeros<double>({ num_S });

        for (size_t t_iter = 0; t_iter < num_T; t_iter++) {
            t = Trange(t_iter);
            for (size_t h_iter = 0; h_iter < num_h; h_iter++) {
                h = Hrange(h_iter);

                line = t_iter * num_h + h_iter;
                std::cout << std::fixed << std::setprecision(2) << "\rRunning... " << 100.0 * (line + 1.0) / num_obs << "%" << std::flush;

                reset();
                relax(num_R, t, h);

                // Sample System
                for (size_t s = 0; s < num_S; s++) {
                    update(t, h);
                    dE = 2. * (J * metric() - h) * grid;
                    Esample(s) = -0.5 * xt::sum(dE)();
                    Msample(s) = xt::sum(grid)();
                }

                results(line, 0) = t;
                results(line, 1) = h;
                results(line, 2) = xt::mean(Esample)() / size;  // Energy
                results(line, 3) = xt::mean(Msample)() / size;  // Magnetization
                results(line, 4) = xt::variance(Esample)() * std::pow(t, -2.) / size;  // Specific Heat Capacity
                results(line, 5) = xt::variance(Msample)() * std::pow(t, -1.) / size;  // Magnetic Susceptibility
            }
        }
        xt::dump_npz("results.npz", "isingmodel", results, false, false);
    }


    void visualize(int frames, int skip, double t, double h) {
        for (size_t frame = 0; frame < frames; frame++) {
            std::string filename = fmt::format("frames/frame{0}.png", frame);
            xt::dump_image(filename, grid);
            relax(skip, t, h);
            std::cout << std::fixed << std::setprecision(2) << "\rRunning... " << 100.0 * (frame + 1.0) / frames << "%" << std::flush;
        }
    }
};