# import numpy as np
# from numba import jit, njit, range
# from numba import int64, float64, typeof
# from numba.experimental import jitclass


# types = [
#     (    'rows',      int64),  # Number Of Rows
#     (    'cols',      int64),  # Number Of Columns
#     (      'nT',      int64),  # Number of T_list
#     (      'sS',      int64),  # Sample Size
#     (      'nR',      int64),  # Number of relaxation updates
#     (      'at', int64[:,:]),  # Ising Lattice
#     (   'scale',    float64),  # Scaling Factor
#     (       'h',    float64),  # Magnetic Field Strength
#     (       'J',    float64),  # Ferromagnetic Coupling Constant
#     (      'kB',    float64),  # Boltzmann Constant
#     (      'Ti',    float64),  # Initial Temperature
#     (      'Tf',    float64),  # Final Temperature
#     (      'Ts', float64[:]),  # Data container for temperature values
#     ( 'Esample', float64[:]),  # Data container for E samples
#     ( 'Msample', float64[:]),  # Data container for M samples
#     (       'E', float64[:]),  # Data container for E
#     (       'M', float64[:]),  # Data container for M
#     (       'C', float64[:]),  # Data container for specific heat capacity
#     (       'X', float64[:]),  # Data container for magnetic susceptibility
# ]

# # Dont delete this, amend it!
# @jitclass(types)
# class IsingLattice(object):
#     def __init__(self, rows, cols, h, J, kB, Ti, Tf, nT, hi, hf, n_h, nR, sS):
#         self.rows, self.cols = rows, cols
#         self.h, self.J, self.kB = h, J, kB
#         self.Ti, self.Tf, self.nT = Ti, Tf, nT
#         self.hi, self.hf, self.n_h = hi, hf, n_h
#         self.Ts = np.linspace(self.Ti, self.Tf, self.nT)
#         self.hs = np.linspace(self.hi, self.hf, self.n_h)
#         self.nR, self.sS = nR, sS
#         self.scale = 1.0 / (self.rows * self.cols)
#         self.at = np.random.choice(np.array([1, -1]), size=(self.rows, self.cols))
#         self.Esample, self.Msample = np.zeros(self.sS), np.zeros(self.sS)
#         self.E, self.M, self.C, self.X = np.zeros(self.nT), np.zeros(self.nT), np.zeros(self.nT), np.zeros(self.nT)

#     def metric_at(self, i, j):
#         return self.at[            (i + 1) % self.rows,                               j] +\
#                self.at[(i - 1 + self.rows) % self.rows,                               j] +\
#                self.at[                              i,             (j + 1) % self.cols] +\
#                self.at[                              i, (j - 1 + self.cols) % self.cols]

#     def metric(self):
#         _ = np.zeros_like(self.at)
#         for i in range(self.rows):
#             for j in range(self.cols):
#                 _[i, j] = self.metric_at(i, j)
#         return _

#     def update(self, T):
#         for i in range(self.rows):
#             for j in range(self.cols):
#                 dE = 2.0 * (self.J * self.metric_at(i, j) - self.h) * self.at[i, j]
#                 prob = 1.0 if dE < 0.0 else np.exp(-dE / (self.kB * T))
#                 if np.random.random() < prob:
#                     self.at[i, j] = -self.at[i, j]            

#     def relax(self, T):
#         for _ in range(self.nR):
#             self.update(T)

#     def measure_at_temperature(self, T):
#         for _ in range(self.sS):
#             self.update(T)
#             dE = 2.0 * (self.J * self.metric() - self.h) * self.at
#             self.Esample[_] = -0.5 * np.sum(dE)
#             self.Msample[_] = np.sum(self.at)
#         E = self.scale * np.mean(self.Esample)
#         M = self.scale * np.mean(self.Msample)
#         C = self.scale * np.var(self.Esample) * T ** (-2)
#         X = self.scale * np.var(self.Msample) * T ** (-1)
#         return T, E, M, C, X

#     def reset(self):
#         self.at = np.random.choice(np.array([1, -1]), size=(self.rows, self.cols))

#     def simulate(self):
#         for t, T in enumerate(self.Ts):
#             print('Running: T =', round(T, 5), '|', 100.0 * t / self.Ts.size, '%')
#             self.reset()
#             self.relax(T)
#             _, self.E[t], self.M[t], self.C[t], self.X[t] = self.measure_at_temperature(T)

#         return self.Ts, self.E, self.M, self.C, self.X


import numpy as np
from numba import int64, float64
from numba.experimental import jitclass


types = [
    (    'rows',        int64),  # Number Of Rows In The Ising Lattice
    (    'cols',        int64),  # Number Of Columns In The Ising Lattice
    (     'n_T',        int64),  # Number Of Temperature Values To Sweep
    (     'n_h',        int64),  # Number Of Magnetic Field Magnitudes To Sweep
    (     'n_S',        int64),  # Sample Size
    (     'n_R',        int64),  # Number Of "Relaxation" Updates To Perform
    (     'h_i',      float64),  # Initial Magnetic Field Magnitude
    (     'h_f',      float64),  # Final Magnetic Field Magnitude
    (       'J',      float64),  # Ferromagnetic Coupling Constant
    (     'k_B',      float64),  # Boltzmann's Constant
    (     'T_i',      float64),  # Initial Temperature Value
    (     'T_f',      float64),  # Final Temperature Value
    (   'scale',      float64),  # Scaling Factor Correcting For Lattice Size
    (  'h_list',   float64[:]),  # An array Of magnetic field magnitudes
    (  'T_list',   float64[:]),  # An array Of temperature values
    ('E_sample',   float64[:]),  # A Data Container For Energy Samples
    ('M_sample',   float64[:]),  # A Data Container For Magnetization Samples
    (       'E', float64[:,:]),  # A Data Container For Energy
    (       'M', float64[:,:]),  # A Data Container For Magnetization
    (       'C', float64[:,:]),  # A Data Container For Specific Heat Capacity
    (       'X', float64[:,:]),  # A Data Container For Magnetic Susceptibility
    (      'at',   int64[:,:]),  # The Ising Lattice
]

@jitclass(types)
class IsingLattice(object):
    def __init__(self, cols, rows, J, k_B, T_i, T_f, n_T, h_i, h_f, n_h, n_R, n_S):
        ## Assign Inputted Object Attributes
        self.rows, self.cols = rows, cols
        self.J, self.k_B = J, k_B
        self.T_i, self.T_f, self.n_T = T_i, T_f, n_T
        self.h_i, self.h_f, self.n_h = h_i, h_f, n_h
        self.n_R, self.n_S = n_R, n_S
        
        ## Assign Created Object Attributes
        self.T_list = np.linspace(self.T_i, self.T_f, self.n_T)
        self.h_list = np.linspace(self.h_i, self.h_f, self.n_h)
        self.scale = 1.0 / (self.rows * self.cols)
        self.at = np.random.choice(np.array([1, -1]), size=(self.rows, self.cols))
        self.E_sample, self.M_sample = np.zeros(self.n_S), np.zeros(self.n_S)
        self.E = np.zeros((self.n_h, self.n_T))
        self.M = np.zeros((self.n_h, self.n_T))
        self.C = np.zeros((self.n_h, self.n_T))
        self.X = np.zeros((self.n_h, self.n_T))

    def metric_at(self, i, j):
        return self.at[              (i + 1) % self.rows,                                 j] +\
               self.at[(i - 1 + self.rows) % self.rows,                                 j] +\
               self.at[                                  i,              (j + 1) % self.cols] +\
               self.at[                                  i, (j - 1 + self.cols) % self.cols]

    def get_E(self):
        return self.scale * np.mean(self.E_sample)
        
    def get_M(self):
        return self.scale * np.mean(self.M_sample)
        
    def get_C(self, T):
        return self.scale * np.var(self.E_sample) * T ** (-2.0)
    
    def get_X(self, T):
        return self.scale * np.var(self.M_sample) * T ** (-1.0)

    def metric(self):
        _ = np.zeros_like(self.at)
        for i in range(self.rows):
            for j in range(self.cols):
                _[i, j] = self.metric_at(i, j)
        return _

    def update(self, h, T):
        for i in range(self.rows):
            for j in range(self.cols):
                dE = 2.0 * (self.J * self.metric_at(i, j) - h) * self.at[i, j]
                prob = 1.0 if dE < 0.0 else np.exp(-dE / (self.k_B * T))
                if np.random.random() < prob:
                    self.at[i, j] = -self.at[i, j]            

    def relax(self, h, T):
        for _ in range(self.n_R):
            self.update(h, T)

    def measure_at(self, h, T):
        for _ in range(self.n_S):
            self.update(h, T)
            dE = 2.0 * (self.J * self.metric() - h) * self.at
            self.E_sample[_] = -0.5 * np.sum(dE)
            self.M_sample[_] = np.sum(self.at)
        return self.get_E(), self.get_M(), self.get_C(T), self.get_X(T)

    def reset(self):
        self.at = np.random.choice(np.array([1, -1]), size=(self.rows, self.cols))

    def simulate(self):
        for h in range(self.n_h):
            H = self.h_list[h]
            for t in range(self.n_T):
                T = self.T_list[t]
                print('Running: h =', round(H, 5) , '| T =', round(T, 5), '|', 100.0 * (h * self.n_T + t) / (self.n_T * self.n_h), '%')
                self.reset()
                self.relax(H, T)
                self.E[h, t], self.M[h, t], self.C[h, t], self.X[h, t] = self.measure_at(H, T)
        return (self.h_list, self.T_list), (self.E, self.M, self.C, self.X)


import numpy as np
import pandas as pd
from tqdm import trange
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


# class realIsingModel:
#     def __init__(self, lattice, nR=200, sS=1000, Ti=1.8, Tf=3.0, nT=1000):
#         self.lattice = lattice
#         self.rows, self.cols = self.lattice.rows, self.lattice.cols
#         self.h, self.J, self.kB = self.lattice.h, self.lattice.J, self.lattice.kB
#         self.nR, self.sS = nR, sS
#         self.Ti, self.Tf, self.nT, self.Ts = Ti, Tf, nT, np.linspace(Ti, Tf, nT)
#         self.T = self.Ti
#         self.E, self.M, self.C, self.X = np.zeros(nT), np.zeros(nT), np.zeros(nT), np.zeros(nT)
        
#     def simulate(self):
#         for t in trange(self.nT, desc='Sweeping Temperatures'):
#             self.lattice.reset()
#             self.lattice.T = self.Ts[t]
#             self.lattice.relax(self.nR)
#             _, self.E[t], self.C[t], self.M[t], self.X[t] = self.lattice.observe(self.sS)       
#         return self.Ts, self.E, self.M, self.C, self.X

#     def visualize(self, t=1.4):
#         self.figsize = np.array([self.cols, self.rows])
#         self.figsize = 16 * self.figsize / np.linalg.norm(self.figsize)
#         self.fig, self.ax = plt.subplots(1,1,figsize=self.figsize, dpi=200, constrained_layout=True)
#         self.fig.suptitle(f'Ising Model (Metropolis-Hastings Algorithm)\nh = {self.h:0.4f} | J = {self.J:0.4f} | T = {self.T:0.4f} [K/kB]')
#         self.lattice.T = t
#         for r in trange(self.nR, desc='Saving Frames'):
#             self.ax.matshow(self.lattice.at, interpolation='bicubic')
#             plt.savefig(f'framedump/frame{str(r).zfill(4)}')
#             plt.cla()
#             self.lattice.relax(1)


# # def main():
# #     p = IsingModel()
# #     Ts, E, C, M, X = p.simulate()
# #     res = pd.DataFrame(
# #         np.vstack((Ts, E, C, M, X)).T, 
# #         columns=['Temperature', 'Energy', 'Specific Heat Capacity', 'Magnetization', 'Magnetic Susceptibility'])
# #     res.to_csv('results.csv')
    
# #     fig, ax = plt.subplots(2, 2, figsize=(32, 32), dpi=200, constrained_layout=True)
# #     fig.suptitle('Ising Model (Metropolis-Hastings Algorithm)')
    
# #     ax[0,0].scatter(res['Temperature'], res['Energy'], marker=',')
# #     ax[0,0].set_ylabel('Energy')
# #     ax[0,0].set_xlabel('Temperature')
# #     ax[0,0].grid()
    
# #     ax[0,1].scatter(res['Temperature'], res['Specific Heat Capacity'], marker=',')
# #     ax[0,1].set_ylabel('Specific Heat Capacity')
# #     ax[0,1].set_xlabel('Temperature')
# #     ax[0,1].grid()
    
# #     ax[1,0].scatter(res['Temperature'], res['Magnetization'], marker=',')
# #     ax[1,0].set_ylabel('Magnetization')
# #     ax[1,0].set_xlabel('Temperature')
# #     ax[1,0].grid()
    
# #     ax[1,1].scatter(res['Temperature'], res['Magnetic Susceptibility'], marker=',')
# #     ax[1,1].set_ylabel('Magnetic Susceptibility')
# #     ax[1,1].set_xlabel('Temperature')
# #     ax[1,1].grid()
    
# #     fig.savefig('results')

# # def main():
# #     p = IsingModel(Ti=0.2)
# #     p.visualize()


