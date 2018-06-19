#!/usr/bin/env python

"""
    What is the largest prime factor of the number 600851475143 ?
"""


import time


def largest_prime_factor (number):
    x = 2
    primes = []
    max_prime_factor = 0

    while number > 1:
        is_prime = True
        for prime in primes:
            if x % prime == 0:
                is_prime = False
                break

        if is_prime == True:
            primes.append(x)
            if number % x == 0 and max_prime_factor < x:
                max_prime_factor = x
                number /= x

        if(x > 2):
            x += 2
        else:
            x += 1

    return max_prime_factor


if __name__ == '__main__':
    start = time.time()
    print largest_prime_factor(600851475143)
    print time.time() - start