#!/usr/bin/env python

"""
    What is the 10 001st prime number?
"""

from time import time

def get_prime (index):
    counter, p = 0, 3
    primes = [2]


    while counter < index - 1:
        is_prime = True

        for prime in primes:
            if p % prime == 0:
                is_prime = False
                break

        if is_prime == True:
            primes.append(p)
            counter += 1

        p += 2

    return primes[-1]

if __name__ == '__main__':
    start = time()
    print get_prime(10001)
    print time() - start