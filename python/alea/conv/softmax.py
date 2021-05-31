import numpy as np


class Softmax:

    def __init__(self, m, n):
        self.W = np.random.randn(m, n) * (2 / m ** 0.5)
        self.b = np.zeros(n)

    def forward(self, x):
        x = x.flatten()  # no need for shape any more, combine all conv kernels (13*13*8=1352, )

        y = np.dot(x, self.W) + self.b  # linear function

        exp = np.exp(y - y.max())  # numerator (softmax(x) === softmax(x + c))

        return exp / np.sum(exp, axis=0)

    def backward(self, eta):
