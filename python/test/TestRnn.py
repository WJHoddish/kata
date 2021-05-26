import random

import numpy as np

from alea import RNN, vocab_size, train_data, create_inputs
from alea.rnn_data import test_data


def softmax(xs):
    return np.exp(xs) / sum(np.exp(xs))


rnn = RNN(vocab_size, 2)  # input neurons, binary classification


def run(data, back_prop=True):
    items = list(data.items())
    random.shuffle(items)

    acc = 0
    loss = 0

    for x, y in items:
        inputs = create_inputs(x)
        target = int(y)  # 0, 1

        # forward
        z, h = rnn.forward(inputs)
        p = softmax(z)

        # calculate acc, loss
        acc += int(np.argmax(p) == target)
        loss -= np.log(p[target])

        if back_prop:
            # examine loss (dL/dy)
            eta = p
            eta[target] -= 1

            # backward
            rnn.backward(eta)

    return acc / len(data), loss / len(data)


if __name__ == '__main__':
    for epoch in range(1000):
        train_acc, train_loss = run(train_data)

        if epoch % 10 == 9:
            print('--- Epoch %d' % (epoch + 1))
            print('Train:\tLoss %.3f | Accuracy: %.3f' % (train_loss, train_acc))

            test_acc, test_loss = run(test_data, back_prop=False)
            print('Test:\tLoss %.3f | Accuracy: %.3f' % (test_loss, test_acc))
