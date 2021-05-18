from abc import ABC

import numpy as np

from .activation import ActivationBase


class Sigmoid(ActivationBase):

    def __init__(self):
        super().__init__()

    def fn(self, x):
        return 1 / (1 + np.exp(-x))

    def grad(self, x):
        n = self.fn(x)

        return n * (1 - n)

    def grad2(self, x):
        """
        Second derivative.
        :param x:
        :return:
        """

        n = self.fn(x)

        return n * (1 - n) * (1 - 2 * n)
