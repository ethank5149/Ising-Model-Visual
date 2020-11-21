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


