class SGD:

    def __init__(self, params, lr):
        self.params = params
        self.lr = lr

    def update(self):
        for p in self.params:
            p.data *= 0.8  # regular term

            p.data -= self.lr * p.grad
