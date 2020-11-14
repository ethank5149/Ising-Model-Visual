import numpy as np
from numpy.random import default_rng
from tqdm.auto import trange
import matplotlib.pyplot as plt
import os


class Ising:
    def __init__(self, 
        rows=1000,     # Number Of Rows
        cols=1000,     # Number Of Columns
        h=0.0,         # Magnetic Field Strength
        J=1.0,         # Ferromagnetic Coupling Constant
        frames = 500,  # Number Of Recorded Frames
        T = 0.5        # Temperature
        ):

        self.rows, self.cols, self.frames = rows, cols, frames
        self.h, self.J, self.T, self.k_B = h, J, T, 1.0
        self.rng = default_rng()
        self.grids = self.rng.choice([-1, 1], size=(self.frames, self.rows, self.cols))
        self.figsize = np.array([self.cols, self.rows])                  # Create a figsize array matching the lattice
        self.figsize = 16 * self.figsize / np.linalg.norm(self.figsize)  # Scale down, preserving aspect ratio 
        self.fig, self.ax = plt.subplots(1, 1, figsize=self.figsize, dpi=200, constrained_layout=True)
        self.fig.suptitle('Ising Model (Metropolis-Hastings Algorithm)')
      

    def update(self, i):
        neighbors = np.roll(self.grids[i-1], 1, axis=0) + np.roll(self.grids[i-1], -1, axis=0) + np.roll(self.grids[i-1], 1, axis=1) + np.roll(self.grids[i-1], -1, axis=1)
        dE = 2.0 * (self.J * neighbors - self.h) * self.grids[i-1]
        probabilities = np.exp(-dE / (self.k_B * self.T))
        composite_probabilities = np.where(dE < 0.0, np.ones_like(self.grids[i-1]), probabilities)
        self.grids[i] = np.where(np.logical_and(self.rng.random(size=self.grids[i-1].shape) < composite_probabilities, self.rng.choice([True, False], size=self.grids[i-1].shape)), np.negative(self.grids[i-1]), self.grids[i-1])


    def run(self):
        for i in trange(self.frames, desc='Running Model'):
            self.update(i)


    def save_grids(self):
        np.save('grids', self.grids)


    def save_frames(self, load_existing=False, **kwargs):
        for i in trange(self.frames, desc='Saving Frame Images'):
            self.ax.matshow(self.grids[i])
            plt.savefig('frames/frame_'+str(i).zfill(4))
            plt.cla()


    def save_video(self, fps=24):
        self.save_frames()
        os.system(f'ffmpeg -framerate {fps} -i frames/frame_%04d.png output.mp4')


def main():
    p = Ising()
    p.run()
    p.save_video()


if __name__ == '__main__':
    main()
