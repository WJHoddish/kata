from alea.layer.layer import Layer


class Net(Layer):
    
    def __init__(self, configs):
        self.layers = []
        self.params = []
        
        for config in configs:
            self.layers.append(self.create_layer(config))
    
    def forward(self, x):
        for layer in self.layers:
            x = layer.forward(x)
        return x
    
    def backward(self, eta):
        for layer in self.layers[::-1]:
            eta = layer.backward(eta)
        return eta
    
    def create_layer(self, config):
        """
        Create layer according to given configs.
        :param config:
        :return:
        """
        
        t = config['type']
        
        if t == 'linear':
            pass
        
        return
