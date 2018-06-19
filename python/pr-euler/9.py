#!/usr/bin/env python

"""
    A Pythagorean triplet is a set of three natural numbers, a  b  c, for which,

    a^2 + b^2 = c^2

    There exists exactly one Pythagorean triplet for which a + b + c = 1000.
    Find the product abc.
"""

from time import time

def pythagorean_product (sum):
    p, q = 2, 1
    limit = sum / 2

    while p < limit:
        while q < p:

            a = p ** 2 - q ** 2
            b = 2 * p * q
            c = p ** 2 + q ** 2

            if a + b + c == sum:
                return a * b * c

            if p % 2 == 0:
                q += 1 + q % 2
            else:
                q += 2 - q % 2

        q = 1
        p += 1

if __name__ == '__main__':
    start = time()
    print pythagorean_product(1000)
    print time() - start