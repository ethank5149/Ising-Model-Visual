import numpy as np
from numpy.random import default_rng
from tqdm import trange
import matplotlib.pyplot as plt


class Ising:
    def __init__(self, 
        rows=1000,          # Number of rows
        cols=1000,          # Number of columns
        frames=250,         # Number of Saved Frames
        T=1.05,             # Temperature
        h=0.0,              # Magnetic Field Strength
        J=1.0,              # Ferromagnetic Coupling Constant
        iter_per_frame = 5  # Number of updates between saved frames
        ):

        self.rows, self.cols = rows, cols
        self.T, self.h, self.J = T, h, J
        self.frames, self.iter_per_frame = frames, iter_per_frame
        self.rng = default_rng()
        self.k_B = 1.0
        self.grid = self.rng.choice([-1, 1], size=(self.rows, self.cols))
        self.data = np.zeros((self.frames, self.rows, self.cols))
        self.fig, self.ax = plt.subplots(1, 1, figsize=(16, 16), dpi=200, constrained_layout=True)
        self.ax.matshow(self.grid)  ##


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


    def save_grid(self, i):
        self.data[i,:,:] = self.grid


    def save_frames(self):
        print('Saving Frame Images...')
        for i in trange(self.data.shape[0]):
            self.ax.matshow(self.data[i], interpolation='bicubic')
            self.ax.set_title('Ising Model (Metropolis-Hastings Algorithm)')
            plt.savefig('plots/frame_'+str(i).zfill(4))
            plt.cla()
        print('Done!\n')


    def save_data(self):
        print('Saving Array...')
        np.save('data', self.data)
        print('Done!\n')


    def run(self):
        print('Running Model...')
        for i in trange(self.frames * self.iter_per_frame):
            self.update()
            if i%self.iter_per_frame==0:
                self.save_grid(i//self.iter_per_frame)
        print('Done!\n')


def main():
    p = Ising()
    p.run()
    p.save_frames()


if __name__ == '__main__':
    main()