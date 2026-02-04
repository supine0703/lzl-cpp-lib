
***Use [MIT License](./LICENSE)***

中文 | [English](./README.md)

# about lzl-cpp-lib <!-- omit in toc -->

这里收集了我常用的 `CMake + C++` 项目的配置，我认为这些是有用的。
我所有的测试都是基于： `MSVC` 、 `Clang` 和 `GCC`。
我主要使用 `c++17` 以上，也尽力在 `c++11` 上兼容。

# 目录 <!-- omit in toc -->

- [环境](#环境)
- [项目内容](#项目内容)
  - [CMake 配置](#cmake-配置)
  - [函数萃取](#函数萃取)
  - [输出类型](#输出类型)
  - [Qt 项目模板](#qt-项目模板)

# 环境

- CMake 3.31.3
- Visual Studio 17 2022
- MinGW 14.2.0
- Clang 19.1.6

# 项目内容

## CMake 配置

[cmake/README](./cmake/README.md)

我将我常用的 `CMake` 配置，包括 `Linux` 和 `Windows` 上。这对于绝大多数项目来说是通用的，同时我还封装了一些有用的 cmake 函数，以便我更好的去构建一些复杂的项目，包含这些内容应该尽可能的放在配置的开头位置。

例如，你可以使用以下代码将这个配置包含到你的项目中：

```cmake
# Set the cmake module path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Import the relevant cmake configuration
include(compiler_settings)
include(copy_lib_interface_headers)
include(copy_dirs_if_diff)
include(auto_install_post_build)
include(generate_lib_exports_header)

# Include headers directory which copy_lib_interface_headers output
include_directories(${LIB_INTERFACE_HEADERS_INCLUDEDIR})
```

## 函数萃取

[functional/README](./utils/functional/README.md)

函数萃取可以提取函数类型做一些特定的行为，比如可以从模板函数中萃取出类型，来达到隐式调用模板函数；也可以萃取成员函数的父类，以达到用类指针和函数指针作为参数。

- [function_traits](./utils/functional/function_traits.h)
  - 函数萃取，用于获取函数返回值，参数列表等，主要会用在模板中
  - 目前测试可以萃取所有函数类型：普通函数、函数指针、标准库函数、成员函数。

```cpp
struct Test {
    void* value;
    void printValue(int64_t num) { std::cout << num << std::endl; }
};
template <typename Func>
static void readValue(lzl::utils::trains_class_type<Func>* object, Func read_func) {
    using arg_type = typename lzl::utils::function_traits<Func>::template arg<0>::type;
    static_assert(lzl::utils::function_traits<Func>::arity == 1);
    (object->*read_func)(reinterpret_cast<arg_type>(object->value));
}
void test() {
    Test test{reinterpret_cast<void*>(10)};
    readValue(&test, &Test::printValue);
}
```

更多内容可以查看这个仓库 [supine0703/qt-settings](https://github.com/supine0703/qt-settings).

## 输出类型

- [TypeName](./utils/type/cxx17/typename.h)
  - 由于 `gcc` 提供的 `typeid(T).name()` 比较难以观察调试，不直观。
  - 因此封装了 `TypeName<T>::value()` 更直接，更方便观察
  - example: 
    ```cpp
    TypeName<void (*)(size_t)>::value();  // return: void (*)(unsigned long long)
    ```

## Qt 项目模板

- [qt-cmake-template](./QtProjectTemplate/README.md)
  - 基于 `CMake` 的 `Qt` 项目模板，包含常用的配置和封装
  - 主要是自用，支持 `Qt 5` 和 `Qt 6`，支持 `MSVC`, `MinGW` 和 `Clang`，支持 `QtCreator` 和 `VSCode` 联合开发
  - 包含引入常用的第三方库 `spdlog`, `hidapi` 的方法 （这一条只在 `Windows` 上测试通过，其他未进行测试）
