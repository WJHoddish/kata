from abc import ABC

import numpy as np

from .activation import ActivationBase


class Tanh(ActivationBase, ABC):

    def __init__(self):
        """
        Hyperbolic tangent function.
        """

        super().__init__()

    def fn(self, x):
        return np.tanh(x)

    def grad(self, x):
        return 1 - np.tanh(x) ** 2  # square

    def grad2(self, x):
        n = np.tanh(x)

        return -2 * n * (1 - n ** 2)
