<!--License: MIT
    Copyright (c) 2024 Li Zonglin (李宗霖) github: <https://github.com/supine0703>
    Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>
-->

***Use [MIT License](./LICENSE)***


# about lzl-cpp-lib <!-- omit in toc -->

I will put my own cpp library here, I think these are useful. 
我会将我自己使的cpp库放在这里，我觉得这些是有用的。


# 目录 <!-- omit in toc -->

- [项目目录](#项目目录)


# 项目目录

- [TypeName](./type/typename.h):
  - 由于 `typeinfo` 提供的 `typeid::name` 比较难以观察调试，不直观。
  - 因此封装了 `TypeName<T>::value()` 更直接，更方便观察
  - example: 
    ```cpp
    // TypeName<void (*)(size_t)>::value();  // return: void (*)(unsigned long long)
    ```
- [function_traits](./functional/function_traits.h):
  - 函数萃取，用于获取函数返回值，参数列表等，主要会用在模板中
  - 目前测试可以萃取所有函数类型：普通函数、函数指针、标准库函数、成员函数。

