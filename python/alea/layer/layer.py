from abc import abstractmethod, ABC

import numpy as np


class Layer(ABC):

    @abstractmethod
    def forward(self, *args):
        pass

    @abstractmethod
    def backward(self, *args):
        pass


class Softmax(Layer):

    def forward(self, x):
        v = np.exp(x - x.max(axis=-1, keepdims=True))

        return v / v.sum(axis=-1, keepdims=True)

    def backward(self):
        pass
