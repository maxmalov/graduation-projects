#!/usr/bin/env python

"""
    Find the sum of all the primes below two million.
"""

from time import time

def primes_sum (limit):
    primes, res = [2], 2
    p = 3

    while p < limit:

        is_prime = True

        for prime in primes:
            if p % prime == 0:
                is_prime = False
                break

        if is_prime == True:
            primes.append(p)
            res += p

        p += 2

    return res

if __name__ == '__main__':
    start = time()
    print primes_sum(2000000)
    print time() - start