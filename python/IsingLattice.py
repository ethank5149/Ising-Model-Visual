# import numpy as np
# from numba import jit, njit, prange
# from numba import int64, float64, typeof
# from numba.experimental import jitclass


# types = [
#     (    'rows',      int64),  # Number Of Rows
#     (    'cols',      int64),  # Number Of Columns
#     (      'nT',      int64),  # Number of Temperatures
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
#     ( 'Esample', float64[:]),  # Data container for energy samples
#     ( 'Msample', float64[:]),  # Data container for magnetization samples
#     (       'E', float64[:]),  # Data container for energy
#     (       'M', float64[:]),  # Data container for magnetization
#     (       'C', float64[:]),  # Data container for specific heat capacity
#     (       'X', float64[:]),  # Data container for magnetic susceptibility
# ]

# # Dont delete this, amend it!
# @jitclass(types)
# class IsingLattice(object):
#     def __init__(self, rows, cols, h, J, kB, Ti, Tf, nT, hi, hf, nh, nR, sS):
#         self.rows, self.cols = rows, cols
#         self.h, self.J, self.kB = h, J, kB
#         self.Ti, self.Tf, self.nT = Ti, Tf, nT
#         self.hi, self.hf, self.nh = hi, hf, nh
#         self.Ts = np.linspace(self.Ti, self.Tf, self.nT)
#         self.hs = np.linspace(self.hi, self.hf, self.nh)
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
from numba import jit, njit, prange
from numba import int64, float64, typeof
from numba.experimental import jitclass


types = [
    (                          'height',      int64), 
    (                           'width',      int64),
    (          'number_of_temperatures',      int64),
    (                     'sample_size',      int64),
    (      'number_of_relaxation_steps',      int64),
    (                           'scale',    float64),
    ('initial_magnetic_field_magnitude',    float64),
    (  'final_magnetic_field_magnitude',    float64),
    ( 'ferromagnetic_coupling_constant',    float64),
    (                     'k_boltzmann',    float64),
    (             'initial_temperature',    float64),
    (               'final_temperature',    float64),
    (       'magnetic_field_magnitudes', float64[:]),
    (                    'temperatures', float64[:]),
    (                   'energy_sample', float64[:]),
    (            'magnetization_sample', float64[:]),
    (                          'energy', float64[:,:]),
    (                   'magnetization', float64[:,:]),
    (          'specific_heat_capacity', float64[:,:]),
    (         'magnetic_susceptibility', float64[:,:]),
    (                              'at', int64[:,:]),

]

# Dont delete this, amend it!
@jitclass(types)
class IsingLattice(object):
    def __init__(self, 
        width, height, 
        ferromagnetic_coupling_constant, k_boltzmann, 
        initial_temperature, final_temperature, number_of_temperatures, 
        initial_magnetic_field_magnitude, final_magnetic_field_magnitude, number_of_magnetic_field_magnitudes, 
        number_of_relaxation_steps, sample_size):

        self.height, self.width = height, width
        self.ferromagnetic_coupling_constant, self.k_boltzmann = ferromagnetic_coupling_constant, k_boltzmann
        self.initial_temperature, self.final_temperature, self.number_of_temperatures = initial_temperature, final_temperature, number_of_temperatures
        self.initial_magnetic_field_magnitude, self.final_magnetic_field_magnitude, self.number_of_magnetic_field_magnitudes = initial_magnetic_field_magnitude, final_magnetic_field_magnitude, number_of_magnetic_field_magnitudes
        self.number_of_relaxation_steps, self.sample_size = number_of_relaxation_steps, sample_size
        
        self.temperatures = np.linspace(self.initial_temperature, self.final_temperature, self.number_of_temperatures)
        self.magnetic_field_magnitudes = np.linspace(self.initial_magnetic_field_magnitude, self.final_magnetic_field_magnitude, self.number_of_magnetic_field_magnitudes)
        self.scale = 1.0 / (self.height * self.width)
        self.at = np.random.choice(np.array([1, -1]), size=(self.height, self.width))
        self.energy_sample, self.magnetization_sample = np.zeros(self.sample_size), np.zeros(self.sample_size)
        self.energy = np.zeros((self.number_of_magnetic_field_magnitudes, self.number_of_temperatures))
        self.magnetization = np.zeros((self.number_of_magnetic_field_magnitudes, self.number_of_temperatures))
        self.specific_heat_capacity = np.zeros((self.number_of_magnetic_field_magnitudes, self.number_of_temperatures))
        self.magnetic_susceptibility = np.zeros((self.number_of_magnetic_field_magnitudes, self.number_of_temperatures))

    def metric_at(self, i, j):
        return self.at[              (i + 1) % self.height,                                 j] +\
               self.at[(i - 1 + self.height) % self.height,                                 j] +\
               self.at[                                  i,              (j + 1) % self.width] +\
               self.at[                                  i, (j - 1 + self.width) % self.width]

    def metric(self):
        _ = np.zeros_like(self.at)
        for i in range(self.height):
            for j in range(self.width):
                _[i, j] = self.metric_at(i, j)
        return _

    def update(self, h, T):
        for i in range(self.height):
            for j in range(self.width):
                dE = 2.0 * (self.ferromagnetic_coupling_constant * self.metric_at(i, j) - h) * self.at[i, j]
                prob = 1.0 if dE < 0.0 else np.exp(-dE / (self.k_boltzmann * T))
                if np.random.random() < prob:
                    self.at[i, j] = -self.at[i, j]            

    def relax(self, h, T):
        for _ in range(self.number_of_relaxation_steps):
            self.update(h, T)

    def measure_at(self, h, T):
        for _ in range(self.sample_size):
            self.update(h, T)
            dE = 2.0 * (self.ferromagnetic_coupling_constant * self.metric() - h) * self.at
            self.energy_sample[_] = -0.5 * np.sum(dE)
            self.magnetization_sample[_] = np.sum(self.at)
        E = self.scale * np.mean(self.energy_sample)
        M = self.scale * np.mean(self.magnetization_sample)
        C = self.scale * np.var(self.energy_sample) * T ** (-2)
        X = self.scale * np.var(self.magnetization_sample) * T ** (-1)
        return h, T, E, M, C, X

    def reset(self):
        self.at = np.random.choice(np.array([1, -1]), size=(self.height, self.width))

    def simulate(self):
        for h in range(self.number_of_magnetic_field_magnitudes):
            for t in range(self.number_of_temperatures):
                print('Running: h =', round(self.magnetic_field_magnitudes[h], 5) , '| T =', round(self.temperatures[t], 5), '|', 100.0 * (h * self.number_of_temperatures + t) / (self.number_of_temperatures * self.number_of_magnetic_field_magnitudes), '%')
                self.reset()
                self.relax(h, T)
                _, _, self.energy[h, t], self.magnetization[h, t], self.specific_heat_capacity[h, t], self.magnetic_susceptibility[h, t] = self.measure_at(h, T)
        return self.magnetic_field_magnitudes, self.temperatures, self.energy.flatten(), self.magnetization.flatten(), self.specific_heat_capacity.flatten(), self.magnetic_susceptibility.flatten()
