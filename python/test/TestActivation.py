import unittest

import numpy as np

from net.activation import *


class Test(unittest.TestCase):

    def test_ReLU(self):
        """
        ReLU, the activation function.
        :return:
        """

        a = ReLU()

        self.assertEqual(a.fn(np.arange(-3, 3)).tolist(),
                         np.array([0, 0, 0, 0, 1, 2]).astype(float).tolist())

    def test_Sigmoid(self):
        a = Sigmoid()

        self.assertEqual(a.fn(0),
                         0.5)
