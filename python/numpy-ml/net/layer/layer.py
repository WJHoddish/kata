from abc import ABC, abstractmethod


class LayerBase(ABC):

    def __init__(self):
        pass

    @abstractmethod
    def forward(self):
        raise NotImplementedError

    @abstractmethod
    def backward(self):
        raise NotImplementedError
