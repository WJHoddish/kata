import numpy as np


def softmax(x):
    v = np.exp(x - x.max(axis=-1, keepdims=True))

    return v / v.sum(axis=-1, keepdims=True)


class CrossEntropy:

    def __call__(self, a, y):
        """
        
        :param a: predictions, network's output
        :param y: true values, binary labels (0, 1)
        :return:
        """

        self.a = softmax(a)
        self.y = y

        p = (np.argmax(self.a, axis=-1) == np.argmax(self.y, axis=-1)).mean()  # mark correct answer as True

        e = -1 * np.einsum('ij,ij->', self.y, np.log(self.a + np.finfo(float).eps)) / y.shape[0]

        return p, e

    def grad(self):
        return self.a - self.y
