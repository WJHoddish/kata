import numpy as np


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


class Conv3x3:

    def __init__(self, core):
        """
        A 3x3 layer.
        :param core:
        """

        self.core = core

        self.filters = np.random.randn(core, 3, 3) / 9  # divide by 9: reduce the variance (Xavier Initialization)

    def forward(self, x):
        h, w = x.shape

        y = np.zeros((h - 2, w - 2, self.core))

        for r, i, j in iterate(x):
            # each time produce a region
            y[i, j] = np.sum(r * self.filters, axis=(1, 2))

        return y
