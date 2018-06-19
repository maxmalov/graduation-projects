#!/usr/bin/env python

"""
    What is the greatest product of four adjacent numbers in any direction
    (up, down, left, right, or diagonally) in the 20x20 grid?
"""

from time import time

def read_grid (filename, separator):
    grid = []
    f = open(filename, 'r')

    for line in f:
        grid.append(map(int, line.rstrip().split(separator)))

    return grid

def greatest_adjanced_numbers_product (grid, count):

    pr, max_pr = 1, 0

    # horizontal
    for i in xrange(len(grid)):
        for j in xrange(len(grid[i]) - count + 1):
            for k in xrange(0,count):
                pr *= grid[i][j + k]
            if pr > max_pr:
                max_pr = pr
            pr = 1

    # vertical
    pr = 1
    for i in xrange(len(grid) - count + 1):
        for j in xrange(len(grid[i])):
            for k in xrange(0,count):
                pr *= grid[i + k][j]
            if pr > max_pr:
                max_pr = pr
            pr = 1

    # diag straight

    pr = 1
    for i in xrange(len(grid) - count + 1):
        for j in xrange(len(grid[i]) - count + 1):
            for k in xrange(0,count):
                pr *= grid[i + k][j + k]
            if pr > max_pr:
                max_pr = pr
            pr = 1

    # diag reverse
    pr = 1
    for i in xrange(count - 1, len(grid)):
        for j in xrange(len(grid[i]) - count + 1):
            for k in xrange(0,count):
                pr *= grid[i - k][j + k]
            if pr > max_pr:
                max_pr = pr
            pr = 1

    return max_pr


if __name__ == '__main__':
    start = time()
    grid = read_grid('input', ' ')
    print greatest_adjanced_numbers_product(grid, 4)
    print time() - start