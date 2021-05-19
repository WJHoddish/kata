from .layer import Layer


class Net(Layer):

    def __init__(self, configs):
        self.layers = []  # multiple layers become a network
        self.params = []

        for config in configs:
            self.add_layer(config)

    def forward(self, x):
        pass

    def backward(self, eta):
        pass

    def add_layer(self, config):
        layer = None

        # select layer (switch-case)
        t = config['type']

        if t == 'linear':
            pass

        # append layer to list
        if layer is None:
            raise RuntimeError
        else:
            self.layers.append(layer)
