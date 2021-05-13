import unittest

from abc import abstractmethod, ABC


class A(ABC):
    def __init__(self):
        print("A()")

    @abstractmethod
    def func(self):
        print("A.func()")


class B(A, ABC):
    def __init__(self):
        super().__init__()

        print("B()")

    def func(self):
        print("B.func()")


class TestAbstractMethod(unittest.TestCase):
    def test(self):
        b = B()

        b.func()  # B.func()
