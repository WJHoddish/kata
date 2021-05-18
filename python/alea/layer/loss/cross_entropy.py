import numpy as np

from alea import Softmax


class CrossEntropy:
    
    def __init__(self):
        self.classifier = Softmax()
    
    def __call__(self, a, y):
        """
        
        :param a:
        :param y:
        :return: both accuracy and loss value.
        """
        
        a = self.classifier.forward(a)
        p = np.argmax(a, axis=-1) == np.argmax(y, axis=-1)  # mark correct answer as True
        
        return p.mean(), -1 * np.einsum('ij,ij->', y, np.log(a)) / y.shape[0]
