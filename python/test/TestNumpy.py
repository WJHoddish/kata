import unittest

import numpy as np


def check(x):
    print("check matrix:")
    print(x.shape)
    print(x)
    print("complete!\n")


a = np.array([[1, 2, 3], [4, 5, 6]])


class TestNumpy(unittest.TestCase):

    def test_normal(self):
        t = a.T

        check(t)

    def test_einsum(self):
        s = np.einsum('ij->i', a)

        check(s)

    def test_eindot(self):
        d = np.einsum('ij,jk->ik', a, a.T)

        check(d)

        check(np.dot(a, a.T))
