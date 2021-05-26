from alea import *


def load(file):
    """
    Parse MNIST .npz files.
    :param file:
    :return:
    """

    file = np.load(file)

    X = file['X']
    Y = file['Y']

    return X.reshape(len(X), -1), Y


def train(nn):
    # load data
    X, Y = load('MNIST/train_set.npz')

    data_size = X.shape[0]  # 60000

    # set hyper-parameters
    lr = 0.001  # learning rate
    fn = CrossEntropy()  # loss function
    optimizer = Momentum(nn.params, lr)
    batch_size = 128

    # train process
    for loop in range(1000):
        acc = 0

        i = 0
        j = 0
        while i <= data_size - batch_size:
            # select a range of data
            x = X[i:i + batch_size]
            y = Y[i:i + batch_size]

            i += batch_size
            j += 1

            # feed to network
            a = nn.forward(x)
            batch_acc, batch_loss = fn(a, y)
            eta = fn.grad()  # get loss function's gradient (dL/dy)
            nn.backward(eta)
            optimizer.update()

            print("loop: %d, batch: %5d, batch acc: %2.1f, batch loss: %.2f" % (loop, i, batch_acc * 100, batch_loss))

            # update acc
            acc = (acc * (j - 1) + batch_acc) / j

        # check acc of this loop
        if acc * 100 > 95:
            break

    return nn


def test(nn):
    X, Y = load('MNIST/test_set.npz')

    data_size = X.shape[0]  # 10000

    correct = 0

    for i in range(data_size):
        if np.argmax(nn.forward(X[i]), axis=-1) == np.argmax(Y[i], axis=-1):
            correct += 1

    print("acc:", correct / data_size * 100)


if __name__ == '__main__':
    # set up network
    layers = [
        {'type': 'linear', 'shape': (784, 200)},
        {'type': 'relu'},
        {'type': 'linear', 'shape': (200, 100)},
        {'type': 'relu'},
        {'type': 'linear', 'shape': (100, 100)},
        {'type': 'relu'},
        {'type': 'linear', 'shape': (100, 100)},
        {'type': 'relu'},
        {'type': 'linear', 'shape': (100, 10)}
    ]

    test(train(Net(layers)))
