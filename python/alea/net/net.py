from .activation import Relu
from .layer import Layer
from .linear import Linear


class Net(Layer):

    def __init__(self, configs):
        self.layers = []  # multiple layers become a network

        self.params = []  # store W, b of each layer

        for config in configs:
            self.add_layer(config)

    def forward(self, x):
        for layer in self.layers:
            x = layer.forward(x)

        return x

    def backward(self, eta):
        for layer in self.layers[::-1]:
            eta = layer.backward(eta)

        return eta

    def add_layer(self, config):
        layer = None

        # select layer (switch-case)
        t = config['type']

        if t == 'linear':
            layer = Linear(**config)  # unpack dictionary

            self.params.append(layer.W)
            self.params.append(layer.b)
        elif t == 'relu':
            layer = Relu()

        # append layer to list
        if layer is None:
            raise RuntimeError
        else:
            self.layers.append(layer)
