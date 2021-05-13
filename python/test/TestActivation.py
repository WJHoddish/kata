import unittest

from net.activation.sigmoid import *


class Test(unittest.TestCase):

    def test_ReLU(self):
        """
        ReLU, the activation function.
        :return:
        """
        pass

    def test_Sigmoid(self):
        a = Sigmoid()

        self.assertEqual(a.fn(0), 0.5)
