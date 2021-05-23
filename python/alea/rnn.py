import numpy as np
from numpy.random import randn

from rnn_data import train_data

vocab = list(set([w for text in train_data.keys() for w in text.split(' ')]))
vocab_size = len(vocab)  # 18

# create word bag
word_to_idx = {w: i for i, w in enumerate(vocab)}
idx_to_word = {i: w for i, w in enumerate(vocab)}


def create_input(text):
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

        self.Whh = randn(hidden_size, hidden_size) / 1000
        self.Wxh = randn(hidden_size, input_size) / 1000
        self.Why = randn(output_size, hidden_size) / 1000

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

        for i in range(len(x)):
            h = np.tanh(self.Wxh @ x[i] + self.Whh @ h + self.bh)
            self.h[i + 1] = h

        # output
        y = self.Why @ h + self.by

        return y, h

    def backward(self, eta, lr=1e-3):
        pass


def softmax(xs):
    return np.exp(xs) / sum(np.exp(xs))


rnn = RNN(vocab_size, 2)  # input neurons, binary classification

out, hid = rnn.forward(create_input('i am very good'))
