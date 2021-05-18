import matplotlib.pyplot as plt

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
    batch_size = 0

    # load data
    X, Y = load('MNIST/train_set.npz')

    data_size = X.shape[0]  # 60000

    # train process
    i = 0
    while i <= data_size - batch_size:
        # select a range of data
        x = X[i:i + batch_size]
        y = Y[i:i + batch_size]

        i += batch_size


if __name__ == '__main__':
    train()
