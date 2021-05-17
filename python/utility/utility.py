import numpy as np


def is_binary(z, msg="need binary matrix"):
    """
    Assume the matrix is only made of "0" and "1".
    :param z:
    :param msg:
    :return:
    """

    assert np.array_equal(z, z.astype(bool)), msg

    return True


def is_stochastic(z, msg="need stochastic matrix"):
    """
    Assume each row is a CDF.
    :param z:
    :param msg:
    :return:
    """

    assert len(z[z < 0]) == len(z[z > 1]) == 0, msg  # probabilities: [0, 1]
    assert np.allclose(  # equal within a tolerance
        np.sum(z, axis=1),  # sum each row
        np.ones(z.shape[0])
    ), msg

    return True


def is_symmetric(z):
    return np.allclose(z, z.T)
