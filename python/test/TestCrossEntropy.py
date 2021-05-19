from alea import *

if __name__ == '__main__':
    fn = CrossEntropy()

    print(fn(np.array([0.1, 0.2, 0.3, 0.4]), np.array([0, 0, 0, 1])))
