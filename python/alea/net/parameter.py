class Parameter:

    def __init__(self, data):
        self.data = data
        self.grad = None

    @property
    def T(self):
        return self.data.T
