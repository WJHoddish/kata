import numpy as np


class MaxPool2x2:

    @staticmethod
    def iterate(img):
        h, w, _ = img.shape

        for i in range(h // 2):
            for j in range(w // 2):
                yield img[(i * 2):(i * 2 + 2), (j * 2):(j * 2 + 2)], i, j  # step: 2

    def forward(self, x):
        h, w, num_filters = x.shape

        y = np.zeros((h // 2, w // 2, num_filters))  # create an empty canvas filled by 0

        for region, i, j in self.iterate(x):
            y[i, j] = np.amax(region, axis=(0, 1))  # select max value in a matrix

        return y
