import numpy as np


class Conv3x3:

    def __init__(self, core):
        """
        A 3x3 layer.
        :param core: number of conv cores
        """
        self.x = None

        self.core = core
        self.filters = np.random.randn(core, 3, 3) / 9  # divide by 9: reduce the variance (Xavier Initialization)

    @staticmethod
    def iterate(img):
        """
        3x3 by default.
        :param img:
        :return:
        """

        h, w = img.shape

        for i in range(h - 2):
            for j in range(w - 2):
                yield img[i:(i + 3), j:(j + 3)], i, j

    def forward(self, x):
        self.x = x

        h, w = x.shape

        y = np.zeros((h - 2, w - 2, self.core))

        for r, i, j in self.iterate(x):
            # each time produce a region
            y[i, j] = np.sum(r * self.filters, axis=(1, 2))

        return y

    def backward(self, eta, lr=.005):
        """

        :param eta: dL/dy
        :param lr:
        :return: dL/df ()
        """

        d_L_f = np.zeros(self.filters.shape)

        for region, i, j in self.iterate(self.x):
            for f in range(self.core):
                d_L_f[f] += eta[i, j, f] * region

        # update params
        self.filters -= lr * d_L_f
