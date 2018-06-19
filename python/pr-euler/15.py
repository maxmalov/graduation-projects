#!/usr/bin/env python

"""
    Starting in the top left corner of a 2x2 grid,
    there are 6 routes (without backtracking) to the bottom right corner.

    How many routes are there through a 20x20 grid?
"""

"""
    1. All paths have m + n length
    2. Path can go only to the right or to the down

    So each path can be defined by a word of size m + n and which is consisting of m "R" and n "D"
"""

from time import time
from math import factorial


def routes_count(n, m):
    return factorial(n + m) / (factorial(n) * factorial(m))


if __name__ == '__main__':
    start = time()
    print routes_count(20, 20)
    print time() - start
