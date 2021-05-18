from abc import ABC, abstractmethod


class ObjectiveBase(ABC):

    def __init__(self):
        super().__init__()

    def __call__(self, y, fx):  # __call__ is inheritable
        """

        :param y: true
        :param fx: predictions
        :return:
        """
        return self.loss(y, fx)

    @abstractmethod
    def loss(self, y, fx):
        raise NotImplementedError

    @abstractmethod
    def grad(self, y, fx, **kwargs):
        raise NotImplementedError


class SquaredError(ObjectiveBase):  # L2 loss

    def __init__(self):
        super().__init__()

    def loss(self, y, fx):
        return 0.5 * np.linalg.norm(fx - y) ** 2

    def grad(self, y, fx, **kwargs):
        return (fx - y) * kwargs["fn"].grad(kwargs["x"])


class CrossEntropy(ObjectiveBase):

    def __init__(self):
        super().__init__()

    def loss(self, y, fx):
        is_binary(y)
        is_stochastic(fx)

        eps = np.finfo(float).eps  # eps is a small positive value

        return -np.sum(
            y  # true distribution (0 or 1)
            *
            np.log(fx + eps)  # prevent zeros
        )

    def grad(self, y, fx, **kwargs):
        is_binary(y)
        is_stochastic(fx)

        return fx - y  # solve derivative via classified discussion
