import numpy as np


class Softmax:

    def __init__(self, m, n):
        self.s = None
        self.x = None
        self.y = None

        self.W = np.random.randn(m, n) * (2 / m ** 0.5)
        self.b = np.zeros(n)

    def forward(self, x):
        """
        x ==linear function==> y ==softmax==> a
        :param x:
        :return:
        """

        # record: shape before flattened
        self.s = x.shape

        x = x.flatten()  # no need for shape any more, combine all conv kernels (13*13*8=1352, )

        # record: raw input
        self.x = x

        # linear function
        y = np.dot(x, self.W) + self.b  # (10, )

        # record: linear function result
        self.y = y

        exp = np.exp(y - y.max())  # numerator (softmax(x) === softmax(x + c))
        return exp / np.sum(exp, axis=0)

    def backward(self, eta, lr=.005):
        """

        :param eta: dL/da (a: probabilities)
        :param lr: learning rate
        :return:
        """

        for i, grad in enumerate(eta):
            if grad == 0:
                continue

            exp = np.exp(self.y)
            S = np.sum(exp)

            # da/dy
            d_a_y = -1 * exp[i] * exp / (S ** 2)
            d_a_y[i] = exp[i] * (S - exp[i]) / (S ** 2)

            # dy/dW
            d_y_W = self.x
            d_y_b = 1
            d_y_x = self.W  # (1352, 10)

            d_L_y = grad * d_a_y

            # dL/dW ...
            d_L_x = d_y_x @ d_L_y
            d_L_W = d_y_W[np.newaxis].T @ d_L_y[np.newaxis]
            d_L_b = d_L_y * d_y_b

            # update params
            self.W -= lr * d_L_W
            self.b -= lr * d_L_b

            return d_L_x.reshape(self.s)
