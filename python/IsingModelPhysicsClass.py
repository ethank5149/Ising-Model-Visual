import numpy as np
from numpy.random import default_rng
from tqdm.auto import trange
import matplotlib.pyplot as plt
import pandas as pd


class Ising:
    def __init__(self, 
        nrows=15,  # Number of rows
        ncols=15,  # Number of columns
        h=0.0,     # Magnetic Field Strength
        J=1.0,     # Ferromagnetic Coupling Constant
        nR = 200,  # Number of relaxation iterations done for each temperature
        sS = 500,  # Number of observations from each temperature
        Ti = 1.50,  # Initial Temperature
        Tf = 2.75,  # Final Temperature
        nT = 200,  # Number of temperature values
        kB = 1.0   # Boltzmann's Constant
        ):

        ## Parameters
        self.nrows, self.ncols = nrows, ncols
        self.scale = 1.0 / (self.nrows * self.ncols)
        self.nR, self.sS = nR, sS
        self.Ti, self.Tf, self.nT = Ti, Tf, nT
        self.h, self.J, self.kB = h, J, kB

        ## Instantiate a single random number generator
        self.rng = default_rng()
    
        ## Data structures
        self.temperatures = np.linspace(self.Ti, self.Tf, self.nT)
        self.ensemble = self.rng.choice([-1, 1], size=(self.sS, self.nrows, self.ncols))
        self.results = pd.DataFrame(np.zeros((self.nT, 5)), columns=[
            'Temperature',
            'Energy', 
            'Specific Heat Capacity', 
            'Magnetization', 
            'Magnetic Susceptibility'])


    def reset(self):
        self.ensemble = self.rng.choice([-1, 1], size=(self.sS, self.nrows, self.ncols))


    def neighbors(self):
        return np.roll(self.ensemble, 1, axis=1) + np.roll(self.ensemble, -1, axis=1) + np.roll(self.ensemble, 1, axis=2) + np.roll(self.ensemble, -1, axis=2)


    def dE(self):
        return 2.0 * (self.J * self.neighbors() - self.h) * self.ensemble


    def probability(self):
        return np.where(self.dE() < 0.0, np.ones_like(self.ensemble), np.exp(-self.dE() / (self.kB * self.T)))


    def update(self):
        # FIXME: Traditional method leads to oscillating behavior and overcorrection
        # self.ensemble = np.where(self.rng.random(size=self.ensemble.shape) < self.probability(), np.negative(self.ensemble), self.ensemble)
        self.ensemble = np.where(np.logical_and(self.rng.random(size=self.ensemble.shape) < self.probability(), self.rng.choice([True, False], size=self.ensemble.shape)), np.negative(self.ensemble), self.ensemble)


    def relax(self):
        for _ in trange(self.nR, desc='Relaxing The Ensemble', leave=False):
            self.update()


    def get_energy(self):
        return -0.5 * np.sum(self.dE(), axis=(1, 2))


    def get_magnetization(self):
        return np.sum(self.ensemble, axis=(1, 2))


    def record(self, i):
        E = self.get_energy()
        M = self.get_magnetization()
        self.results.at[i,             'Temperature'] = self.T
        self.results.at[i,                  'Energy'] = np.mean(E, axis=0) * self.scale
        self.results.at[i,  'Specific Heat Capacity'] =  np.var(E, axis=0) * self.scale / self.T ** 2
        self.results.at[i,           'Magnetization'] = np.mean(M, axis=0) * self.scale
        self.results.at[i, 'Magnetic Susceptibility'] =  np.var(M, axis=0) * self.scale / self.T


    def run(self):
        for iT in trange(self.nT, desc='Sweeping Temperatures'):
            self.T = self.temperatures[iT]
            self.reset()
            self.relax()
            self.record(iT)


    def save(self):
        self.results.to_csv('results.csv')


def main():
    p = Ising()
    p.run()
    p.save()

    fig, ax = plt.subplots(2, 2, figsize=(32, 32), dpi=200, constrained_layout=True)
    fig.suptitle('Ising Model (Metropolis-Hastings Algorithm)')
    ax[0,0].scatter(p.results['Temperature'], p.results[                  'Energy'], marker=',')
    ax[0,1].scatter(p.results['Temperature'], p.results[           'Magnetization'], marker=',')
    ax[1,0].scatter(p.results['Temperature'], p.results[  'Specific Heat Capacity'], marker=',')
    ax[1,1].scatter(p.results['Temperature'], p.results[ 'Magnetic Susceptibility'], marker=',')
    ax[0,0].set_ylabel(           'Energy []')
    ax[0,1].set_ylabel(    'Magnetization []')
    ax[1,0].set_ylabel(  'Specific Heat Capacity []')
    ax[1,1].set_ylabel( 'Magnetic Susceptibility []')
    ax[0,0].set_xlabel('Temperature [K/kB]')
    ax[0,1].set_xlabel('Temperature [K/kB]')
    ax[1,0].set_xlabel('Temperature [K/kB]')
    ax[1,1].set_xlabel('Temperature [K/kB]')
    ax[0,0].grid()
    ax[0,1].grid()
    ax[1,0].grid()
    ax[1,1].grid()
    plt.savefig('results')


if __name__ == '__main__':
    main()
