import numpy as np

from .layer import Layer


class Relu(Layer):

    def __init__(self):
        self.x = None

    def forward(self, x):
        self.x = x  # remember inputs while forwarding

        return np.maximum(0, x)

    def backward(self, eta):
        """

        :param eta: dL/da(i+1)
        :return: dL/da(i) = dL/da(i+1) * da(i+1)/da(i)
        """

        eta[self.x < 0] = 0

        return eta


class Sigmoid:
    pass


class Tanh:
    pass
