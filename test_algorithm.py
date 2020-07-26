nrows = 5
ncols = 5

M = [[0,  1,  2,  3,  4],
     [5,  6,  7,  8,  9],
     [10, 11, 12, 13, 14],
     [15, 16, 17, 18, 19],
     [20, 21, 22, 23, 24]]

# f(0, 0) = 0
# f(0, 1) = 1
# f(0, 2) = 2
# f(0, 3) = 3
# f(0, 4) = 4

# f(1, 0) = 5
# f(1, 1) = 6
# f(1, 2) = 7
# f(1, 3) = 8
# f(1, 4) = 9

# f(4, 4) = 25


m = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
     14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24]

idx = 16
i = idx // nrows
j = idx % nrows

print(f"{M[i][j]} == {m[idx]} ?")


def flatten(i, j):
    return ncols * i + j


neighbors = [flatten((i + 1 + nrows) % nrows, (j + 0 + ncols) % ncols),
             flatten((i + 0 + nrows) % nrows, (j + 1 + ncols) % ncols),
             flatten((i - 1 + nrows) % nrows, (j + 0 + ncols) % ncols),
             flatten((i + 0 + nrows) % nrows, (j - 1 + ncols) % ncols)]
print(neighbors)
print(f"{m[neighbors[0]]}, {m[neighbors[1]]}, {m[neighbors[2]]}, {m[neighbors[3]]}")
