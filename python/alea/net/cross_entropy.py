import numpy as np


def softmax(x):
    v = np.exp(x - x.max(axis=-1, keepdims=True))

    return v / v.sum(axis=-1, keepdims=True)


class CrossEntropy:

    def __call__(self, a, y):
        """
        
        :param a: predictions, network's output
        :param y: true values, binary labels
        :return:
        """

        a = softmax(a)

        p = np.argmax(a, axis=-1) == np.argmax(y, axis=-1).mean()  # mark correct answer as True

        e = -np.sum(y * np.log(a + np.finfo(float).eps))

        return p, e
