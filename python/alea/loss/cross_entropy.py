import numpy as np

from alea import Softmax


class CrossEntropyLoss:

    def __init__(self):
        self.classifier = Softmax()

    def __call__(self, a, y):
        a = self.classifier.forward(a)

        return -1 * np.einsum('ij,ij->', y, np.log(a)) / y.shape[0]
