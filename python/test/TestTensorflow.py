from tensorflow.python.client import device_lib

[print(x) for x in device_lib.list_local_devices() if x.device_type == 'GPU']
