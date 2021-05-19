import numpy as np

from alea import Layer, Parameter


class Linear(Layer):

    def __init__(self, shape):
        """

        :param shape: neurons (m, n)
        """

        self.W = Parameter(np.random.randn(*shape) * (2 / shape[0] ** 0.5))
        self.b = Parameter(np.zeros(shape[-1]))

        self.x = None

    def forward(self, x):
        self.x = x

        return np.dot(x, self.W.data) + self.b.data

    def backward(self, eta):
        batch_size = eta.shape[0]

        self.W.grad = np.dot(self.x.T, eta) / batch_size
        self.b.grad = np.sum(eta, axis=0) / batch_size

        return np.dot(eta, self.W.T)
