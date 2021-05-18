from abc import ABC
from abc import abstractmethod


class ActivationBase(ABC):

    def __init__(self):
        super().__init__()

    def __call__(self, x):  # call as functor
        if x.ndim == 1:
            x = x.reshape(1, -1)

        return self.fn(x)

    @abstractmethod
    def fn(self, x):
        raise NotImplementedError  # like pure virtual function in C++

    @abstractmethod
    def grad(self, x):
        """
        Compute the gradient of the activation function wrt the input.
        :param x:
        :return:
        """

        raise NotImplementedError

    @abstractmethod
    def grad2(self, x):
        raise NotImplementedError
