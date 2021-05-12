# Kata Toolkit

一个服务于ALEA人工智能框架的辅助组件库

## controller

流程控制

### ioc (inversion of control)：反向控制

将生成对象的依赖关系注册给ioc容器，以std::string做标签。通过“标签”和“对应的参数”创建对象。

- 用户获得的对象被std::shared_ptr管理。

## gem

编译期数学计算库（generalized expressions of math）

## more_traits

元编程类型信息萃取方法集合

### function traits

- 对函数，函数对象，lambda表达式的类型萃取工具。

### tuple index

- 检查一个std::tuple，建立一个index数列。其之后将被用于提取tuple中的数值，进而填到其它function中去（kata::fill）。

### type dict

异类词典，提供了一种传参语法糖，使用时将参数的“值”与对应的“标签”关联起来。

## pattern

设计模式模板

### singleton：单例模式

若将一个类定义成单例，则在构造的时候不应有任何依赖，必要的信息就放到模板参数里吧。

- Meyers' Singleton

- CRTP：需要用户类作为模板类型，以确定get instance时的类型；需要用户继承自己，令用户类的构造行为受到限制（需要token类型依赖）。

### visitor：访问者模式

通过模板递归将若干个接受不同（element）类型的纯虚函数（互相是重载关系）塞到visitor base类里。利用了访问者模式中element（即被访问者）数量稳定的特点。

## task

多线程组件库

### thread_pool

- 在主线程中创建thread pool，其开启若干个线程，每个线程函数本质是一个循环。在循环开始时检查条件（若条件不满足则阻塞，等待被唤醒）：pool停止或task不为空，即仅当pool未被停止，且任务队列为空时才会等待。

- enqueue：向thread pool中添加一个任务，在主线程可以获得代表该任务执行结果的future（主线程调用get时将等待相关任务执行完毕）。

###           