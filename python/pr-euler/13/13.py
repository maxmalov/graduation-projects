#!/usr/bin/env python

"""
    Work out the first ten digits of the sum of the following
    one-hundred 50-digit numbers (see input file).
"""

from time import time

def summary (filename, count):
    f = open(filename, 'r')
    res = 0
    for line in f:
        res += int(line.rstrip())
    return str(res)[:count]

if __name__ == '__main__':
    start = time()
    print summary('input', 10)
    print time() - start