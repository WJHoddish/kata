import unittest

from abc import abstractmethod, ABC


class A(ABC):

    def __init__(self):
        print("A()")

    @staticmethod
    def func():
        print("A.func()")

    @abstractmethod
    def am(self, n, **kwargs):
        pass


class B(A):

    def __init__(self):
        super().__init__()

    def am(self, n, **kwargs):
        print(kwargs["b"])


class C(A):

    def __init__(self):
        super().__init__()

    def am(self, n, **kwargs):
        print(kwargs["c"])


# test cases


class Test(unittest.TestCase):

    def test(self):
        b, c = B(), C()

        b.am(1, b="B.am()")
        c.am(1, c="C.am()")
