#!/usr/bin/env python

from time import time

"""
    Find the difference between the sum of the squares
    of the first one hundred natural numbers and the square of the sum.
"""

def sum_square_diff_sum_of_squares (number):
    res = 0
    for x in range(1, number+1):
        for y in range(x+1, number+1):
            res += x * y
    return 2 * res

if __name__ == '__main__':
    start = time()
    print sum_square_diff_sum_of_squares(100)
    print time() - start
