import numpy as np


def is_binary(x, msg="need binary matrix"):
    assert np.array_equal(x, x.astype(bool)), msg
    return True


def is_stochastic(x, msg="need stochastic matrix"):
    # assert len(x[x < 0]) == len(x[x > 1]) == 0, msg  # probabilities: [0, 1]
    assert np.allclose(  # error < 1e-05
        np.sum(x, axis=1),  # sum each row
        np.ones(x.shape[0])
    ), msg
    return True
