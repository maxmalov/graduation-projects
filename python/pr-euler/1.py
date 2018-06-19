#!/usr/bin/env python

"""
    Find the sum of all the multiples of 3 or 5 below 1000
"""


from time import time


def sum_3_5 (limit):
    s = 0
    for x in range(3,limit):
        if x % 3 == 0 or x % 5 == 0:
            s += x
    return s

if __name__ == '__main__':
    start = time()
    print sum_3_5(1000)
    print time() - start