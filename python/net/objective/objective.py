from abc import ABC, abstractmethod

import numpy as np

from utility import greet


class ObjectiveBase(ABC):

    def __init__(self):
        super().__init__()

    def __call__(self, y, fx):  # __call__ is inheritable
        """

        :param y: true
        :param fx: predictions
        :return:
        """
        return self.loss(y, fx)

    @abstractmethod
    def loss(self, y, fx):
        raise NotImplementedError

    @abstractmethod
    def grad(self, y, fx, **kwargs):
        raise NotImplementedError


class SquaredError(ObjectiveBase):  # L2 loss

    def __init__(self):
        super().__init__()

    def loss(self, y, fx):
        return 0.5 * np.linalg.norm(fx - y) ** 2

    def grad(self, y, fx, **kwargs):
        return (fx - y) * kwargs["fn"].grad(kwargs["x"])


class CrossEntropy(ObjectiveBase):

    def __init__(self):
        super().__init__()

    def loss(self, y, fx):
        utility.is_binary(y)
        is_stochastic(fx)

    def grad(self, y, fx, **kwargs):
        pass
