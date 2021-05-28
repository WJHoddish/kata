import numpy as np


def iterate(img):
    h, w, _ = img.shape

    for i in range(h // 2):
        for j in range(w // 2):
            yield img[(i * 2):(i * 2 + 2), (j * 2):(j * 2 + 2)], i, j


class MaxPool2:

    @staticmethod
    def forward(x):
        h, w, num_filters = x.shape
        y = np.zeros((h // 2, w // 2, num_filters))

        for region, i, j in iterate(x):
            y[i, j] = np.amax(region, axis=(0, 1))

        return y
