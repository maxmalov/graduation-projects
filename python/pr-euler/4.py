#!/usr/bin/env python

"""
    A palindromic number reads the same both ways. The largest palindrome
    made from the product of two 2-digit numbers is 9009 = 91 99.

    Find the largest palindrome made from the product of two 3-digit numbers.
"""


import time


"""
    x = 100000a + 10000b + 1000c + 100c + 10b + a
      = 100001a + 10010b + 1100c =
      = 11 (9091a + 910b + 100c)

    Means on of the divisors must be divided by 11
"""
def max_palindrome ():
    max = 0
    for n in range(101,1000)[::-1]:
        for m in range(101,991)[::-11]:
            pr = n * m
            s_pr = str(pr)
            if s_pr == s_pr[::-1] and max < pr:
                max = pr
    return max


if __name__ == '__main__':
    start = time.time()
    print max_palindrome()
    print time.time() - start