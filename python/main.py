from abc import ABC, abstractmethod


def func(n=0):
    print(n)


class A(ABC):

    def __init__(self):
        super().__init__()

    @abstractmethod
    def run(self):
        pass


class B(A, ABC):

    def __init__(self):
        super().__init__()

    def run(self):
        print(0)


class C(A, ABC):

    def __init__(self, n):
        super().__init__()

        self.__n = n

    def run(self):
        print(self.__n)


def poly(a):
    a.run()


class D(ABC):

    def __call__(self):
        self.run()

    def run(self):
        pass


class E(D):

    def run(self):
        print("E.run()")


if __name__ == '__main__':
    assert 1, "zero"
    # b = B()
    # c = C(99)
    #
    # poly(b)
    # poly(c)

    e = E()
    e()
