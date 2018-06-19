#!/usr/bin/env python

"""
    What is the sum of the digits of the number 2^1000?
"""

from time import time

if __name__ == '__main__':
    start = time()
    print sum(int(digit) for digit in str(2 ** 1000))
    print time() - start
