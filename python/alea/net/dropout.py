from .layer import Layer


class Dropout(Layer):

    def __init__(self, dr):
        self.dr = dr
        self.fix = 1 / (1 - dr)

    def forward(self, x):
        pass

    def backward(self, eta):
        pass
