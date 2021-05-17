# Kata Python

引入numpy-ml，一个基于numpy的Python机器学习方法框架。

## 2021.5.13

- 安装numpy（1.20.3）。

- 使用Python提供的单元测试类。

## 2021.5.14

既然多态的意义在于“同样的接口，不同的行为”，在实现abstractmethod时应严格保证“传入”参数的一致，即不提倡使用**kwargs传参。对于一个虚函数，在个别实例类中可能需要额外的参数，办法是将这类参数变成这些类的成员。

##

## 框架结构

### 组件类

- net.activation：激活函数实例类，均继承自ActivationBase，实现fn（原函数），grad（导数），grad2（二阶导数）方法。

- net.objective：目标函数实例类（损失函数）。

- net.layer：层，层级的操作，目的是组合而成大型神经网络（e.g. 全连接层）。

### 算法类

- net.scheduler：针对“学习率衰减”的几种流行策略。

- net.optimizer（losses）：优化算法，常见的对sgd的改进算法（e.g. 动量随机梯度下降）。 交叉熵损失函数；
  
### 其它

- utility：辅助函数，类型判断；特殊常量生成等。

## 杂谈

- numpy中，矩阵+常数即每个元素都+该常数。