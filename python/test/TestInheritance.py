import unittest

from abc import abstractmethod, ABC


class A:
    def __init__(self):
        print("A()")

    @staticmethod
    def func():
        print("A.func()")


class B(A):
    def __init__(self):
        super().__init__()

        print("B()")


class Test(unittest.TestCase):
    def test(self):
        b = B()

        b.func()  # A.func()
