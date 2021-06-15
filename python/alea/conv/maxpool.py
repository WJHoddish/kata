import numpy as np


class MaxPool2x2:

    def __init__(self):
        self.x = None

    @staticmethod
    def iterate(img):
        h, w, _ = img.shape

        for i in range(h // 2):
            for j in range(w // 2):
                yield img[(i * 2):(i * 2 + 2), (j * 2):(j * 2 + 2)], i, j  # step: 2

    def forward(self, x):
        # record: raw input
        self.x = x

        h, w, num_filters = x.shape

        y = np.zeros((h // 2, w // 2, num_filters))  # create an empty canvas filled by 0

        for region, i, j in self.iterate(x):
            y[i, j] = np.amax(region, axis=(0, 1))  # select max value in a matrix

        return y

    def backward(self, eta):
        """

        :param eta: dL/dy
        :return: dL/dx = dL/dy * dy/dx
        """

        d_L_x = np.zeros(self.x.shape)  # (26, 26, 8)

        for region, i, j in self.iterate(self.x):
            h, w, f = region.shape

            m = np.amax(region, axis=(0, 1))

            # traverse the whole region (2x2)
            for i2 in range(h):
                for j2 in range(w):
                    for f2 in range(f):
                        # only watch the pixel with the max value
                        if region[i2, j2, f2] == m[f2]:
                            d_L_x[i * 2 + i2, j * 2 + j2, f2] = eta[i, j, f2]

        return d_L_x
