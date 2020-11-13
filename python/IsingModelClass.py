import numpy as np
from numpy.random import default_rng
from tqdm.auto import trange
import matplotlib.pyplot as plt
import pandas as pd
import os


class Ising:
    def __init__(self, 
        rows=50,                      # Number of rows
        cols=50,                      # Number of columns
        h=0.0,                        # Magnetic Field Strength
        J=1.0,                        # Ferromagnetic Coupling Constant
        fast_forward = 1,             # Number of updates for each saved frame  ## usually one unless speeding up a video
        num_relaxation = 100,         # Number of relaxation iterations done for each temperature  ## Set to zero for videos
        sample_size = 100,            # Number of observations from each temperature  ## Equivalent to the number of frames if making a video
        initial_T = 1.5,              # Initial Temperature
        final_T = 3.5,                # Final Temperature
        num_T = 1000                  # Number of temperature values
        ):

        self.rows, self.cols = rows, cols
        self.h, self.J = h, J
        self.fast_forward = fast_forward
        
        self.num_relaxation = num_relaxation
        self.sample_size = sample_size
        self.initial_T = initial_T
        self.final_T = final_T
        self.num_T = num_T
        self.T_series = np.linspace(self.initial_T, self.final_T, self.num_T)

        self.intrinsic_energies = None
        self.intrinsic_magnetizations = None
        self.specific_heat_capacities = None
        self.intrinsic_magnetic_susceptibilities = None

        self.temperatures = np.repeat(self.T_series, self.sample_size).reshape((self.num_T, self.sample_size))  # TODO: This is ugly
        self.energies = np.zeros_like(self.temperatures)
        self.magnetizations = np.zeros_like(self.energies)

        self.num_runs = self.sample_size * self.fast_forward
        self.num_updates = self.num_T * (self.num_relaxation + self.num_runs)
        
        self.results = None
        self.rng = default_rng()
        self.k_B = 1.0
        self.grid = self.rng.choice([-1, 1], size=(self.rows, self.cols))
        self.grids = np.zeros((self.num_T, self.sample_size, self.rows, self.cols))
        self.grids_size = self.grids.nbytes / 1048576.0

        self.fig, self.ax = plt.subplots(1, 1, figsize=(16, 16), dpi=200, constrained_layout=True)
        self.fig.suptitle('Ising Model (Metropolis-Hastings Algorithm)')


    def summarize(self):
        length = len(f'Fast-Forward [Updates/Obs.]:{self.fast_forward:6.4g}')  # TODO: This is ugly
        print('\nIsing Model Summary')
        print(length*'=')
        print(f'Number Of Rows:             {self.rows           :6.4g}')
        print(f'Number Of Columns:          {self.cols           :6.4g}')
        print(f'B Field Strength (h) []:    {self.h              :6.4g}')
        print(f'Coupling Constant (J) []:   {self.J              :6.4g}')
        print(f'Initial Temp. [K/k_B]:      {self.initial_T      :6.4g}')
        print(f'Final Temp. [K/k_B]:        {self.final_T        :6.4g}')
        print(f'Number Of Temperatures:     {self.num_T          :6.4g}')
        print(f'Relaxation [Updates/Temp.]: {self.num_relaxation :6.4g}')
        print(f'Runs [1/Temp.]:             {self.num_runs       :6.4g}')
        print(f'Observations [1/Run]:       {self.sample_size    :6.4g}')
        print(f'Fast-Forward [Updates/Obs.]:{self.fast_forward   :6.4g}')
        print(f'Total Updates:              {self.num_updates    :6.4g}')
        print(f'Size Of All Grids [MB]:     {self.grids_size     :6.4g}')
        print('\n')


    def get_energy(self):
        return -0.5 * np.sum(self.dE())


    def get_magnetization(self):
        return np.sum(self.grid)


    def neighbors(self):
        return np.roll(self.grid, 1, axis=0) + np.roll(self.grid, -1, axis=0) + np.roll(self.grid, 1, axis=1) + np.roll(self.grid, -1, axis=1)


    def dE(self):
        return 2.0 * (self.J * self.neighbors() - self.h) * self.grid


    def probability(self):
        return np.exp(-self.dE() / (self.k_B * self.T))


    def probabilities(self):
        return np.where(self.dE() < 0.0, np.ones_like(self.grid), self.probability())
        

    def update(self):
        self.grid = np.where(np.logical_and(self.rng.random(size=self.grid.shape) < self.probabilities(), self.rng.choice([True, False], size=self.grid.shape)), np.negative(self.grid), self.grid)


    def relax(self, i):
        for _ in range(i):
            self.update()


    def log_observation(self, i_t, i_s):
        self.grids[i_t, i_s, :, :] = self.grid
        self.energies[i_t, i_s] = self.get_energy()
        self.magnetizations[i_t, i_s] = self.get_magnetization()
        

    def compile_results(self):
        self.intrinsic_energies = np.mean(self.energies, axis=1) / (self.rows * self.cols)
        self.intrinsic_magnetizations = np.mean(self.magnetizations, axis=1) / (self.rows * self.cols)
        self.specific_heat_capacities = np.var(self.energies, axis=1) / (self.rows * self.cols * np.power(self.T_series, 2))
        self.intrinsic_magnetic_susceptibilities = np.var(self.magnetizations, axis=1) / (self.rows * self.cols * self.T_series)
        self.results = pd.DataFrame(
            np.vstack((self.intrinsic_energies, self.intrinsic_magnetizations, self.specific_heat_capacities, self.intrinsic_magnetic_susceptibilities, self.T_series)).T,
            columns=['Intrinsic Energy', 'Intrinsic Magnetization', 'Specific Heat Capacity', 'Intrinsic Magnetic Susceptibility', 'Temperature'])


    def save_results(self):
        self.compile_results()
        self.results.to_csv('results.csv')


    def run(self):
        print('Running Model...')
        for i_t in trange(self.T_series.size):
            self.T = self.T_series.flatten()[i_t]
            for _ in range(self.num_relaxation):
                self.update()
            for i_s in trange(self.num_runs, leave=False):
                self.update()
                if i_s % self.fast_forward == 0:
                    self.log_observation(i_t, i_s // self.fast_forward)
        print('Done!\n')


## For Videos
###################################################################################################
    def save_frames(self, load_existing=False, **kwargs):  # TODO: Comment my methodology better in this section
        print('Saving Frame Images...')
        if load_existing:
            self.load_grids(**kwargs)
        for i in trange(self.sample_size):
            self.ax.matshow(self.grids[0, i])  # TODO: Bicubic Interpeolation would be really cool but really slow
            plt.savefig('frames/frame_'+str(i).zfill(4))
            plt.cla()
        print('Done!\n')


    def save_video(self, fps=24):
        assert(self.num_T==1 and self.num_relaxation==0)
        self.save_frames()
        print('Writing to Video...')
        os.system(rf'ffmpeg -framerate {fps} -i frame_%04d.png output.mp4')
        print('Done!\n')
###################################################################################################


def main():
    p = Ising()
    p.run()
    p.save_results()

    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(32, 32), dpi=200, constrained_layout=True)
    fig.suptitle('Ising Model (Metropolis-Hastings Algorithm)')
    ax1.scatter(p.results['Temperature'], p.results['Intrinsic Energy'], marker=',')
    ax2.scatter(p.results['Temperature'], p.results['Intrinsic Magnetization'], marker=',')
    ax3.scatter(p.results['Temperature'], p.results['Specific Heat Capacity'], marker=',')
    ax4.scatter(p.results['Temperature'], p.results['Intrinsic Magnetic Susceptibility'], marker=',')
    ax1.set_ylabel('Intrinsic Energy')
    ax2.set_ylabel('Intrinsic Magnetization')
    ax3.set_ylabel('Specific Heat Capacity')
    ax4.set_ylabel('Intrinsic Magnetic Susceptibility')
    ax1.set_xlabel('Temperature')
    ax2.set_xlabel('Temperature')
    ax3.set_xlabel('Temperature')
    ax4.set_xlabel('Temperature')
    ax1.grid()
    ax2.grid()
    ax3.grid()
    ax4.grid()
    fig.savefig('results')


def test_video():
    p = Ising(num_relaxation=0, num_T=1, initial_T=1.2, rows=500, cols=500, sample_size=500)
    p.run()
    p.save_video()

if __name__ == '__main__':
    test_video()
    # main()

