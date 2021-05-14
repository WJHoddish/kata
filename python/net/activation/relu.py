from abc import ABC

import numpy as np

from .activation import ActivationBase


class ReLU(ActivationBase):

    def __init__(self):
        """
        Rectified Linear Unit, the most common one.
        """
        super().__init__()

    def fn(self, x):
        return np.clip(
            x,
            0,  # min
            np.inf  # max
        )

    def grad(self, x):
        return (x > 0).astype(int)  # bool to int

    def grad2(self, x):
        return np.zeros_like(x)


class LeakyReLU(ActivationBase):

    def __init__(self, alpha=0.3):
        """
        Allow negative value.
        :param alpha:
        """
        super().__init__()

        self.alpha = alpha  #

    def fn(self, x):
        res = x.copy()
        res[x < 0] = res[x < 0] * self.alpha

        return res

    def grad(self, x):
        res = np.ones_like(x)
        res[x < 0] *= self.alpha  # always not zero

        return res

    def grad2(self, x):
        return np.zeros_like(x)  # generate a zero matrix with the same size of input ndarray
