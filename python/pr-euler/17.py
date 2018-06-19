#!/usr/bin/env python

"""
    If the numbers 1 to 5 are written out in words: one, two, three, four, five,
    hen there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

    If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words,
    how many letters would be used?


    NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two)
    contains 23 letters and 115 (one hundred and fifteen) contains 20 letters.
    The use of "and" when writing out numbers is in compliance with British usage.
"""

from time import time


def number_digits_letters_count():
    res = 0

    # 1 - 9
    res += (3 + 3 + 5 + 4 + 4 + 3 + 5 + 5 + 4)  # = 36

    # 10 - 19
    res += (3 + 6 + 6 + 8 + 8 + 7 + 7 + 9 + 8 + 8)  # = 70

    # 20 - 99
    res += (10 * (6 + 6 + 5 + 5 + 5 + 7 + 6 + 6) + 8 * 36)  # = 748

    # 100 - 999
    res += (36 * 100 + (36 + 70 + 748) * 9 + 7 * 9 + 9 * 99 * 10)

    return res + 11


if __name__ == '__main__':
    start = time()
    print number_digits_letters_count()
    print time() - start
