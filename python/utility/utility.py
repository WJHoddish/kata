import numpy as np


def is_binary(x, msg="need binary matrix"):
    assert np.array_equal(x, x.astype(bool)), msg

    return True


def is_stochastic(z, msg="need stochastic matrix"):
    """
    Assume each row is a cdf.
    :param z:
    :param msg:
    :return:
    """

    assert len(x[x < 0]) == len(x[x > 1]) == 0, msg  # probabilities: [0, 1]
    assert np.allclose(  # equal within a tolerance
        np.sum(x, axis=1),  # sum each row
        np.ones(x.shape[0])
    ), msg

    return True


def is_symmetric(z):
    return np.allclose(z, z.T)
