import numpy as np


class Momentum(object):

    def __init__(self, params, lr, beta=0.9):
        self.params = params
        self.lr = lr

        self.beta = beta
        self.grads = [np.zeros(p.data.shape) for p in self.params]

    def update(self):
        for p, grad in zip(self.params, self.grads):
            # update accumulated gradients
            np.copyto(grad, self.beta * grad + (1 - self.beta) * p.grad)

            p.data -= self.lr * grad
