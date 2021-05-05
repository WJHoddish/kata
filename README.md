# Kata Toolkit

一个服务于ALEA人工智能框架的辅助组件库

## gem

## more_traits

元编程类型信息萃取方法集合

### function traits

- 对函数，函数对象，lambda表达式的类型萃取工具。

### tuple index

- 检查一个std::tuple，建立一个index数列。其之后将被用于提取tuple中的数值，进而填到其它function中去（kata::fill）。

## pattern

设计模式模板

### singleton：单例模式

-

## task

多线程组件库

### thread_pool

- 在主线程中创建thread pool，其开启若干个线程，每个线程函数本质是一个循环。在循环开始时检查条件（若条件不满足则阻塞，等待被唤醒）：pool停止或task不为空，即仅当pool未被停止，且任务队列为空时才会等待。

- enqueue：向thread pool中添加一个任务，在主线程可以获得代表该任务执行结果的future（主线程调用get时将等待相关任务执行完毕）。

###       