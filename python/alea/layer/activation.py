import numpy as np

from .layer import Layer


class Relu(Layer):

    def __init__(self, x):
        self.x = x

    def forward(self, x):
        return np.maximum(0, x)

    def backward(self, eta):
        eta[self.x <= 0] = 0

        return eta
