import matplotlib.pyplot as plt

from TestMnist import load
from alea import Conv3x3

if __name__ == '__main__':
    X, Y = load('MNIST/train_set.npz')

    x = X[1]


    def show(img):
        plt.matshow(img)
        plt.show()


    conv = Conv3x3(8)
    y = conv.forward(X[0].reshape(28, 28))

    # display the result of each kernel
    for i in range(8):
        show(y[:, :, i])
