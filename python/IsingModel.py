import numpy as np
from numba import int64, float64
from numba.experimental import jitclass


types = [
    (                          'rows',      int64),  # Number Of Rows In The Ising Lattice
    (                          'cols',      int64),  # Number Of Columns In The Ising Lattice
    (                           'n_T',      int64),  # Number Of Temperature Values To Sweep
    (                           'n_h',      int64),  # Number Of Magnetic Field Magnitudes To Sweep
    (                           'n_S',      int64),  # Sample Size
    (                           'n_R',      int64),  # Number Of "Relaxation" Updates To Perform
    (                           'h_i',    float64),  # Initial Magnetic Field Magnitude
    (                           'h_f',    float64),  # Final Magnetic Field Magnitude
    (                             'J',    float64),  # Ferromagnetic Coupling Constant
    (                           'k_B',    float64),  # Boltzmann's Constant
    (                           'T_i',    float64),  # Initial Temperature Value
    (                           'T_f',    float64),  # Final Temperature Value
    (                         'scale',    float64),  # Scaling Factor Correcting For Lattice Size
    ('magnetic_field_magnitude_range', float64[:]),
    (             'temperature_range', float64[:]),
    (                 'energy_sample', float64[:]),
    (          'magnetization_sample', float64[:]),
    (                             'H', float64[:]),  # A Data Container For Magnetic Field Magnitudes
    (                             'T', float64[:]),  # A Data Container For Temperatures
    (                             'E', float64[:]),  # A Data Container For Energy
    (                             'M', float64[:]),  # A Data Container For Magnetization
    (                             'C', float64[:]),  # A Data Container For Specific Heat Capacity
    (                             'X', float64[:]),  # A Data Container For Magnetic Susceptibility
    (                            'at', int64[:,:]),  # The Ising Lattice
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
        self.temperature_range = np.linspace(self.T_i, self.T_f, self.n_T)
        self.magnetic_field_magnitude_range = np.linspace(self.h_i, self.h_f, self.n_h)
        self.scale = 1.0 / (self.rows * self.cols)
        self.at = np.random.choice(np.array([1, -1]), size=(self.rows, self.cols))

        self.energy_sample, self.magnetization_sample = np.zeros(self.n_S), np.zeros(self.n_S)
        self.H = np.zeros(self.n_h * self.n_T)
        self.T = np.zeros(self.n_h * self.n_T)
        self.E = np.zeros(self.n_h * self.n_T)
        self.M = np.zeros(self.n_h * self.n_T)
        self.C = np.zeros(self.n_h * self.n_T)
        self.X = np.zeros(self.n_h * self.n_T)

    def metric_at(self, i, j):
        return self.at[            (i + 1) % self.rows,                               j] +\
               self.at[(i - 1 + self.rows) % self.rows,                               j] +\
               self.at[                              i,             (j + 1) % self.cols] +\
               self.at[                              i, (j - 1 + self.cols) % self.cols]

    def get_E(self):
        return self.scale * np.mean(self.energy_sample)
        
    def get_M(self):
        return self.scale * np.mean(self.magnetization_sample)
        
    def get_C(self, temperature):
        return self.scale * np.var(self.energy_sample) * temperature ** (-2.0)
    
    def get_X(self, temperature):
        return self.scale * np.var(self.magnetization_sample) * temperature ** (-1.0)

    def metric(self):
        _ = np.zeros_like(self.at)
        for i in range(self.rows):
            for j in range(self.cols):
                _[i, j] = self.metric_at(i, j)
        return _

    def update(self, magnetic_field_magnitude, temperature):
        for i in range(self.rows):
            for j in range(self.cols):
                dE = 2.0 * (self.J * self.metric_at(i, j) - magnetic_field_magnitude) * self.at[i, j]
                prob = 1.0 if dE < 0.0 else np.exp(-dE / (self.k_B * temperature))
                if np.random.random() < prob:
                    self.at[i, j] = -self.at[i, j]            

    def relax(self, magnetic_field_magnitude, temperature):
        for _ in range(self.n_R):
            self.update(magnetic_field_magnitude, temperature)

    def measure_at(self, magnetic_field_magnitude, temperature):
        for _ in range(self.n_S):
            self.update(magnetic_field_magnitude, temperature)
            dE = 2.0 * (self.J * self.metric() - magnetic_field_magnitude) * self.at
            self.energy_sample[_] = -0.5 * np.sum(dE)
            self.magnetization_sample[_] = np.sum(self.at)
        return magnetic_field_magnitude, temperature, self.get_E(), self.get_M(), self.get_C(temperature), self.get_X(temperature)

    def reset(self):
        self.at = np.random.choice(np.array([1, -1]), size=(self.rows, self.cols))

    def simulate(self):
        for i_h in range(self.n_h):
            magnetic_field_magnitude = self.magnetic_field_magnitude_range[i_h]
            for i_t in range(self.n_T):
                temperature = self.temperature_range[i_t]
                line = i_h * self.n_T + i_t
                print('Running:', 100.0 * line / (self.n_T * self.n_h), '%')
                self.reset()
                self.relax(magnetic_field_magnitude, temperature)
                self.H[line], self.T[line], self.E[line], self.M[line], self.C[line], self.X[line] = self.measure_at(magnetic_field_magnitude, temperature)
        return self.H, self.T, self.E, self.M, self.C, self.X
