import matplotlib.pyplot as plt
import numpy as np

from TestMnist import load
from alea import Conv3x3, MaxPool2x2, Softmax


def show(img):
    """
    Display 2x2 image.
    :param img:
    :return:
    """

    plt.matshow(img)
    plt.show()


# prepare layers
conv = Conv3x3(8)
pool = MaxPool2x2()
softmax = Softmax(13 * 13 * 8, 10)


def forward(x, y):
    """
    Forward path, focus on 1 image only.
    :param x: image
    :param y: label
    :return:
    """

    # normalize input images [-0.5, 0.5], feed to conv
    a = conv.forward((x / 255) - 0.5)

    # 2nd layer: 2x2 pooling
    a = pool.forward(a)

    # linear layer (activation: softmax)
    a = softmax.forward(a)

    # cross-entropy error
    e = -np.log(a[y])
    p = 1 if np.argmax(a) == y else 0

    return a, e, p  # output, loss, accuracy


def train(x, y, backward=True):
    y = np.argmax(y)

    # forward
    a, e, p = forward(x, y)

    if backward:
        grad = np.zeros(10)
        grad[y] = -1 / a[y]  # dL/da

        # backward
        grad = softmax.backward(grad)
        grad = pool.backward(grad)
        grad = conv.backward(grad)

    return e, p  # loss, accuracy (result of this epoch)


if __name__ == '__main__':

    for j in range(3):

        # train
        X, Y = load('MNIST/train_set.npz', False)

        loss = 0
        true = 0

        for i, (image, label) in enumerate(zip(X, Y)):

            if i % 10000 == 9999:
                print(
                    '[Step %d] Past 100 steps: Loss %.3f | Accuracy: %d%%' %
                    (i + 1, loss / 100, true)
                )

                # reset after one epoch
                loss = 0
                true = 0

            err, acc = train(image, label)
            loss += err
            true += acc

        # test
        X, Y = load('MNIST/test_set.npz', False)

        loss = 0
        true = 0

        for i, (image, label) in enumerate(zip(X, Y)):
            err, acc = train(image, label, False)  # no backward
            loss += err
            true += acc

        print(
            'Test Set Accuracy:', true / X.shape[0] * 100
        )
