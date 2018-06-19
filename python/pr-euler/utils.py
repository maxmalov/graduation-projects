#!/usr/bin/env python

class Primes:

    def __init__ (self):
        self._primes = [2, 3]
        self.to_begin()


    def to_begin (self):
        self._current = 0


    def get_next (self):

        if self._current < len(self._primes) - 1:
            self._current += 1
            return self._primes[self._current]

        p = self._primes[-1] + 2

        while True:
            is_prime = True

            for prime in self._primes:
                if p % prime == 0:
                    is_prime = False
                    break

            if is_prime:
                self._primes.append(p)
                self._current += 1
                return p

            p += 2

    def get_current (self):
        return self._primes[self._current]