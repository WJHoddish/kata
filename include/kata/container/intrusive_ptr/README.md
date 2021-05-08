# intrusive_ptr

## ref_count_base

- 析构时若引用计数大于1则视为非法：调用std::terminate()退出。

## weak_view_template

- 继承自ref_count_base且禁用复制，故使用多继承。

## intrusive_base

- 使用了private继承（它的删除器D，同时是它的模板参数之一）：CRTP？

- 