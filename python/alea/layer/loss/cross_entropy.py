import numpy as np


def softmax(x):
    v = np.exp(x - x.max(axis=-1, keepdims=True))

    return v / v.sum(axis=-1, keepdims=True)


class CrossEntropy:

    def __call__(self, a, y):
        """
        
        :param a: network output
        :param y: binary labels
        :return: both accuracy and loss value.
        """

        a = softmax(a)
        p = np.argmax(a, axis=-1) == np.argmax(y, axis=-1)  # mark correct answer as True

        eps = np.finfo(float).eps

        return p.mean(), -np.sum(y * np.log(a + eps))
