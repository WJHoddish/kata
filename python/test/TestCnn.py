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


# read data
X, Y = load('MNIST/train_set.npz', False)

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

    y = np.argmax(y)

    # cross-entropy error
    e = -np.log(a[y])
    p = 1 if np.argmax(a) == y else 0

    return a, e, p  # output, loss, accuracy


if __name__ == '__main__':
    # run
    loss = 0
    true = 0

    for i, (image, label) in enumerate(zip(X, Y)):
        out, err, acc = forward(image, label)

        loss += err
        true += acc

        if i % 100 == 99:
            print(
                '[Step %d] Past 100 steps: Loss %.3f | Accuracy: %d%%' %
                (i + 1, loss / 100, true)
            )

            # reset after one epoch
            loss = 0
            true = 0
