import numpy as np
from numpy.random import default_rng
from tqdm.auto import trange
import matplotlib.pyplot as plt
import pandas as pd


class Ising:
    def __init__(self, 
        rows=50,            # Number of rows
        cols=50,            # Number of columns
        h=0.0,              # Magnetic Field Strength
        J=1.0,              # Ferromagnetic Coupling Constant
        relax = 500,        # Number of relaxation iterations done for each temperature
        sample_size = 100,  # Number of observations from each temperature
        T_i = 1.5,          # Initial Temperature
        T_f = 3.5,          # Final Temperature
        num_T = 1000        # Number of temperature values
        ):

        self.rows, self.cols = rows, cols
        self.h, self.J = h, J
        self.relax, self.sample_size = relax, sample_size

        self.T_i, self.T_f, self.num_T = T_i, T_f, num_T
        self.T_series = np.linspace(self.T_i, self.T_f, self.num_T)

        self.temperatures = np.repeat(self.T_series, self.sample_size).reshape((self.num_T, self.sample_size))  # TODO: This is ugly
        self.energy_sample = np.zeros_like(self.temperatures)
        self.magnetization_sample = np.zeros_like(self.energy_sample)
        
        self.rng = default_rng()
        self.k_B = 1.0
        self.grid = self.rng.choice([-1, 1], size=(self.rows, self.cols))


    def get_energy(self):
        return -0.5 * np.sum(self.dE())


    def get_magnetization(self):
        return np.sum(self.grid)


    def neighbors(self):
        return np.roll(self.grid, 1, axis=0) + np.roll(self.grid, -1, axis=0) + np.roll(self.grid, 1, axis=1) + np.roll(self.grid, -1, axis=1)


    def dE(self):
        return 2.0 * (self.J * self.neighbors() - self.h) * self.grid
        

    def update(self):
        dE = self.dE()
        probabilities = np.exp(-dE / (self.k_B * self.T))
        composite_probabilities = np.where(dE < 0.0, np.ones_like(self.grid), probabilities)
        self.grid = np.where(np.logical_and(self.rng.random(size=self.grid.shape) < composite_probabilities, self.rng.choice([True, False], size=self.grid.shape)), np.negative(self.grid), self.grid)
        

    def log_observation(self, i_t, i_s):
        self.energy_sample[i_t, i_s] = self.get_energy()
        self.magnetization_sample[i_t, i_s] = self.get_magnetization()


    def compile_results(self):
        self.intrinsic_E   = np.mean(self.energy_sample,        axis=1) / (self.rows * self.cols                     )
        self.intrinsic_M   = np.mean(self.magnetization_sample, axis=1) / (self.rows * self.cols                     )
        self.specific_Cv   = np.var( self.energy_sample,        axis=1) / (self.rows * self.cols * self.T_series ** 2)
        self.intrinsic_Chi = np.var( self.magnetization_sample, axis=1) / (self.rows * self.cols * self.T_series     )
        self.results = pd.DataFrame(
            np.vstack((self.intrinsic_E, self.intrinsic_M, self.specific_Cv, self.intrinsic_Chi, self.T_series)).T,
            columns=['Energy', 'Magnetization', 'Specific Heat Capacity', 'Magnetic Susceptibility', 'Temperature'])


    def save_results(self):
        self.compile_results()
        self.results.to_csv('results.csv')


    def run(self):
        for i_t in trange(self.T_series.size, desc='Running Model'):
            self.T = self.T_series.flatten()[i_t]
            for _ in range(self.relax):
                self.update()
            for i_s in range(self.sample_size):
                self.update()
                self.log_observation(i_t, i_s)


def main():
    p = Ising()
    p.run()
    p.save_results()

    fig, ax = plt.subplots(2, 2, figsize=(32, 32), dpi=200, constrained_layout=True)
    fig.suptitle('Ising Model (Metropolis-Hastings Algorithm)')
    ax[0,0].scatter(p.results['Temperature'], p.results['Energy'], marker=',')
    ax[0,1].scatter(p.results['Temperature'], p.results['Magnetization'], marker=',')
    ax[1,0].scatter(p.results['Temperature'], p.results['Specific Heat Capacity'], marker=',')
    ax[1,1].scatter(p.results['Temperature'], p.results['Magnetic Susceptibility'], marker=',')
    ax[0,0].set_ylabel('Energy')
    ax[0,1].set_ylabel('Magnetization')
    ax[1,0].set_ylabel('Specific Heat Capacity')
    ax[1,1].set_ylabel('Magnetic Susceptibility')
    ax[0,0].set_xlabel('Temperature')
    ax[0,1].set_xlabel('Temperature')
    ax[1,0].set_xlabel('Temperature')
    ax[1,1].set_xlabel('Temperature')
    ax[0,0].grid()
    ax[0,1].grid()
    ax[1,0].grid()
    ax[1,1].grid()
    fig.savefig('results')


if __name__ == '__main__':
    main()

