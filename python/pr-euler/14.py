#!/usr/bin/env python

"""
    The following iterative sequence is defined for the set of positive integers:

    n -> n/2 (n is even)
    n -> 3n + 1 (n is odd)

    Using the rule above and starting with 13, we generate the following sequence:

    13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
    It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms.
    Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

    Which starting number, under one million, produces the longest chain?

    NOTE: Once the chain starts the terms are allowed to go above one million.
"""

from time import time
import math


def check_power(number, base):
    power = math.log(number) / math.log(base)
    if power - int(power) == 0:
        return (True, int(power))
    return (False, power)


def sequence_counter(limit):
    max_len = max_len_number = 1
    lengths = {
        "1": 1
    }

    for x in xrange(2, limit):
        curr = x
        curr_len = 1

        while curr > 1:

            if curr in lengths:
                curr_len += lengths[curr]
                break

            power_info = check_power(curr, 2)
            if power_info[0]:
                curr_len += power_info[1] + 1
                break

            if curr % 2 == 0:
                curr = curr / 2
            else:
                curr = 3 * curr + 1

            curr_len += 1

        if curr_len > max_len:
            max_len_number, max_len = x, curr_len

        lengths[x] = curr_len

    return (max_len_number, max_len)


if __name__ == '__main__':
    start = time()
    print sequence_counter(1000000)
    print time() - start
