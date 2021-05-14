import unittest



class Test(unittest.TestCase):

    def test(self):
        def functions(*args, **kwargs):
            print("kwargs= ", kwargs)

        functions(a=1, b=2, c=3, d=4)
