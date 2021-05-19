import numpy as np
from matplotlib import pyplot as plt

from alea import *


def load(file):
    """
    Parse MNIST .npz files.
    :param file:
    :return:
    """

    file = np.load(file)

    return file['X'], file['Y']


def train():
    # load data
    X, Y = load('MNIST/train_set.npz')

    data_size = X.shape[0]  # 60000

    # set up network
    layers = [
        {'type': 'batchnorm', 'shape': 784, 'requires_grad': False, 'affine': False},
        {'type': 'linear', 'shape': (784, 400)},
        {'type': 'batchnorm', 'shape': 400},
        {'type': 'relu'},
        {'type': 'linear', 'shape': (400, 100)},
        {'type': 'batchnorm', 'shape': 100},
        {'type': 'relu'},
        {'type': 'linear', 'shape': (100, 10)}
    ]

    net = layers

    # set hyper-parameters
    batch_size = 128
    lr = 0.001  # learning rate
    fn = CrossEntropy()  # loss function

    # train process
    i = 0
    while i <= data_size - batch_size:
        # select a range of data
        x = X[i:i + batch_size]
        y = Y[i:i + batch_size]

        i += batch_size

        # feed to network
