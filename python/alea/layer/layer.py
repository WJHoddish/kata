from abc import abstractmethod, ABC


class Layer(ABC):

    @abstractmethod
    def forward(self, *args):
        pass

    @abstractmethod
    def backward(self, *args):
        pass
