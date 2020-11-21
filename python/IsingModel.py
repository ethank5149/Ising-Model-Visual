import numpy as np
import pandas as pd
from tqdm import trange
from numba import jit, prange
from numba import int64, float64, typeof
from numba.experimental import jitclass
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


isinglattice_types = [
    ('nrows',      int64),  # Number Of Rows
    ('ncols',      int64),  # Number Of Columns
    ('scale',    float64),  # Scaling Factor
    (    'h',    float64),  # Magnetic Field Strength
    (    'J',    float64),  # Ferromagnetic Coupling Constant
    (   'kB',    float64),  # Boltzmann Constant
    (    'T',    float64),  # Temperature
    ( 'grid', int64[:,:]),  # Ising Lattice
]


@jitclass(isinglattice_types)
class IsingLattice(object):
    def __init__(self, nrows, ncols, h, J, kB, T):
        self.nrows, self.ncols = nrows, ncols
        self.scale = 1.0 / (nrows * ncols)
        self.h, self.J, self.kB, self.T = h, J, kB, T
        self.grid = np.random.choice(np.array([1, -1]), size=(self.nrows, self.ncols))

    def siteneighbors(self, i, j):
        return self.grid[             (i + 1) % self.nrows,                                 j] + \
               self.grid[(i - 1 + self.nrows) % self.nrows,                                 j] + \
               self.grid[                                i,              (j + 1) % self.ncols] + \
               self.grid[                                i, (j - 1 + self.ncols) % self.ncols]
    
    def gridneighbors(self):
        _ = np.zeros_like(self.grid)
        for i in range(self.nrows):
            for j in range(self.ncols):
                _[i, j] = self.siteneighbors(i, j)
        return _

    def update(self):
        for i in range(self.nrows):
            for j in range(self.ncols):
                dE = 2.0 * (self.J * self.siteneighbors(i, j) - self.h) * self.grid[i, j]
                prob = 1.0 if dE < 0.0 else np.exp(-dE / (self.kB * self.T))
                if np.random.random() < prob:
                    self.grid[i, j] = -self.grid[i, j]            

    def relax(self, n):
        for _ in range(n):
            self.update()

    def observe(self, s):
        Es, Ms = np.zeros(s), np.zeros(s)
        for _ in range(s):
            self.update()
            dE = 2.0 * (self.J * self.gridneighbors() - self.h) * self.grid
            Es[_] = -0.5 * np.sum(dE)
            Ms[_] = np.sum(self.grid)
        E = self.scale * np.mean(Es)
        M = self.scale * np.mean(Ms)
        C = self.scale * np.var(Es) * self.T ** (-2)
        X = self.scale * np.var(Ms) * self.T ** (-1)
        return self.T, E, M, C, X

    def reset(self):
        self.grid = np.random.choice(np.array([1, -1]), size=(self.nrows, self.ncols))



class IsingModel(object):
    def __init__(self, nrows=1080, ncols=1920, h=0.0, J=1.0, kB=1.0, nR=1000, sS=1000, Ti=1.8, Tf=3.0, nT=1000):
        self.nrows, self.ncols = nrows, ncols
        self.h, self.J, self.kB = h, J, kB
        self.nR, self.sS = nR, sS
        self.Ti, self.Tf, self.nT, self.Ts = Ti, Tf, nT, np.linspace(Ti, Tf, nT)
        self.T = self.Ti
        self.E, self.M, self.C, self.X = np.zeros(nT), np.zeros(nT), np.zeros(nT), np.zeros(nT)
        self.lattice = IsingLattice(self.nrows, self.ncols, self.h, self.J, self.kB, self.Ts[0])

        self.figsize = np.array([self.ncols, self.nrows])
        self.figsize = 16 * self.figsize / np.linalg.norm(self.figsize)
        self.fig, self.ax = plt.subplots(1,1,figsize=self.figsize, dpi=200, constrained_layout=True)
        self.fig.suptitle(f'Ising Model (Metropolis-Hastings Algorithm)\nh = {self.h:0.4f} | J = {self.J:0.4f} | T = {self.T:0.4f} [K/kB]')

    def simulate(self):
        for t in trange(self.nT, desc='Sweeping Temperatures'):
            self.lattice.reset()
            self.lattice.T = self.Ts[t]
            self.lattice.relax(self.nR)
            _, self.E[t], self.C[t], self.M[t], self.X[t] = self.lattice.observe(self.sS)       
        return self.Ts, self.E, self.M, self.C, self.X

    def visualize(self, t=1.4):
        self.lattice.T = t
        for r in trange(self.nR, desc='Saving Frames'):
            self.ax.matshow(self.lattice.grid, interpolation='bicubic')
            plt.savefig(f'framedump/frame{str(r).zfill(4)}')
            plt.cla()
            self.lattice.relax(1)


# def main():
#     p = IsingModel()
#     Ts, E, C, M, X = p.simulate()
#     res = pd.DataFrame(
#         np.vstack((Ts, E, C, M, X)).T, 
#         columns=['Temperature', 'Energy', 'Specific Heat Capacity', 'Magnetization', 'Magnetic Susceptibility'])
#     res.to_csv('results.csv')
    
#     fig, ax = plt.subplots(2, 2, figsize=(32, 32), dpi=200, constrained_layout=True)
#     fig.suptitle('Ising Model (Metropolis-Hastings Algorithm)')
    
#     ax[0,0].scatter(res['Temperature'], res['Energy'], marker=',')
#     ax[0,0].set_ylabel('Energy')
#     ax[0,0].set_xlabel('Temperature')
#     ax[0,0].grid()
    
#     ax[0,1].scatter(res['Temperature'], res['Specific Heat Capacity'], marker=',')
#     ax[0,1].set_ylabel('Specific Heat Capacity')
#     ax[0,1].set_xlabel('Temperature')
#     ax[0,1].grid()
    
#     ax[1,0].scatter(res['Temperature'], res['Magnetization'], marker=',')
#     ax[1,0].set_ylabel('Magnetization')
#     ax[1,0].set_xlabel('Temperature')
#     ax[1,0].grid()
    
#     ax[1,1].scatter(res['Temperature'], res['Magnetic Susceptibility'], marker=',')
#     ax[1,1].set_ylabel('Magnetic Susceptibility')
#     ax[1,1].set_xlabel('Temperature')
#     ax[1,1].grid()
    
#     fig.savefig('results')


def main():
    p = IsingModel(nrows=15, ncols=15)
    Ts, E, C, M, X = p.simulate()

    Tc = 2 / np.log(1 + np.sqrt(2))
    betamodel = lambda T, c, beta : c * (Tc - T) ** beta
    alphamodel = lambda T, c, alpha : c * (T - Tc) ** -alpha

    # (calpha, alpha), _ = curve_fit(alphamodel, Ts, C)
    # (cbeta, beta), _ = curve_fit(betamodel, Ts, M)

    fig, ax = plt.subplots(1, 1, figsize=(16, 16), dpi=200)
    ax.set_title('Ising Model (Metropolis-Hastings Algorithm)\nCritical Exponents About The Critical Temperature')

    betascatter = ax.scatter(Ts, M, marker=',')
    alphascatter = ax.scatter(Ts, C, marker=',')
    # ax.plot(Ts, model(Ts, cbeta, beta), label=rf'$M\sim{cbeta:0.4g}(T_c-T)^{{{beta:0.4g}}}$')
    # ax.plot(Ts, model(Ts, calpha, alpha), label=rf'$C\sim\frac{{{calpha:0.4g}}}{{(T-T_c)^{{{alpha:0.4g}}}}}$')

    ax.grid()
    fig.savefig('IsingModel')


# def main():
#     p = IsingModel(Ti=0.2)
#     p.visualize()

    

if __name__ == '__main__':
    main()
