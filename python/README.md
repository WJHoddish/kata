#                     

## File Structure

- layer.py

层的基类，要求实例类定义前向，后向传播函数。

- activation.py

常见的激活函数，也视作独立的“层”。

- cross_entropy.py

交叉熵损失函数，要求y为独热编码，网络输出a将被softmax。

- parameter.py

@property的意义：将类的方法视为一个属性。

- linear.py

线性层。