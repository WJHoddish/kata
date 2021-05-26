import numpy as np
from numpy.random import randn

from .rnn_data import train_data

vocab = list(set([w for text in train_data.keys() for w in text.split(' ')]))
vocab_size = len(vocab)  # 18

# create word bag
word_to_idx = {w: i for i, w in enumerate(vocab)}
idx_to_word = {i: w for i, w in enumerate(vocab)}


def create_inputs(text):
    """
    Sentence 2 one-hot vector.
    :param text:
    :return:
    """

    res = []

    for w in text.split(' '):
        v = np.zeros((vocab_size, 1))
        v[word_to_idx[w]] = 1
        res.append(v)

    return res


class RNN:

    def __init__(self, input_size, output_size, hidden_size=64):
        """

        :param input_size:
        :param output_size:
        :param hidden_size:
        """

        self.Whh = randn(hidden_size, hidden_size) * (2 / hidden_size ** 0.5)
        self.Wxh = randn(hidden_size, input_size) * (2 / hidden_size ** 0.5)
        self.Why = randn(output_size, hidden_size) * (2 / output_size ** 0.5)

        self.bh = np.zeros((hidden_size, 1))
        self.by = np.zeros((output_size, 1))

        self.x = None  # last input
        self.h = dict()

    def forward(self, x):
        """
        RNN forward.
        :param x:
        :return:
        """

        h = np.zeros((self.Whh.shape[0], 1))  # hidden state

        # cache information
        self.x = x
        self.h = {0: h}

        for i in range(len(x)):
            h = np.tanh(self.Wxh @ x[i] + self.Whh @ h + self.bh)  # activation: tanh
            self.h[i + 1] = h

        # output
        y = self.Why @ h + self.by

        return y, h

    def backward(self, eta, lr=1e-2):
        """

        :param eta: dL/dy (output size, 1)
        :param lr: learning rate
        :return:
        """

        n = len(self.x)

        # dL/dW(hy), dL/db(y)
        d_Why = eta @ self.h[n].T
        d_by = eta

        d_Whh = np.zeros(self.Whh.shape)
        d_Wxh = np.zeros(self.Wxh.shape)
        d_bh = np.zeros(self.bh.shape)

        # how BPTT sets grads
        d_h = self.Why.T @ eta

        for t in reversed(range(n)):
            # dL/dh * (1 - h^2)
            temp = (1 - self.h[t + 1] ** 2) * d_h  # "t", as an index, is used by hidden states

            # dL/db(h) = dL/dh * (1 - h^2)
            d_bh += temp

            # dL/dWhh = dL/dh * (1 - h^2) * h_{t-1}
            print(d_Whh.shape)
            print(temp @ self.h[t].T)
            d_Whh += temp @ self.h[t].T

            # dL/dW(xh) = dL/dh * (1 - h^2) * x
            d_Wxh += temp @ self.x[t].T

            # next dL/dh = dL/dh * (1 - h^2) * W(hh)
            d_h = self.Whh @ temp

        # clip to prevent exploding gradients
        for d in [d_Wxh, d_Whh, d_Why, d_bh, d_by]:
            np.clip(d, -1, 1, out=d)

        # SGD
        self.Whh -= lr * d_Whh
        self.Wxh -= lr * d_Wxh
        self.Why -= lr * d_Why
        self.bh -= lr * d_bh
        self.by -= lr * d_by
