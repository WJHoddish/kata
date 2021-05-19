from abc import abstractmethod, ABC


class Layer(ABC):

    @abstractmethod
    def forward(self, *args):
        raise NotImplementedError

    @abstractmethod
    def backward(self, *args):
        raise NotImplementedError
