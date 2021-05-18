import numpy as np


class Network:

    def __init__(self, sizes):
        self.sizes = sizes

        self.num_layers = len(sizes)

        self.weights = [np.random.randn(y, x) for x, y in zip(sizes[:-1], sizes[1:])]  # w * x
        self.biases = [np.random.randn(y, 1) for y in sizes[1:]]  # no bias for input layer


if __name__ == '__main__':
    nn = Network([2, 3, 1, 4])

    print(nn.weights)
