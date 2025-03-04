
***Use [MIT License](./LICENSE)***

English | [中文](./README_zh.md)

# about lzl-cpp-lib <!-- omit in toc -->

Here is a collection of configurations for my common 'CMake + C++' projects that I find useful.
All my tests are based on: 'MSVC', 'Clang', and 'GCC'.
I mainly use 'c++17' and above, but try to work with 'c++11' as well.

# Table of Contents <!-- omit in toc -->

- [Environment](#environment)
- [Project Content](#project-content)
  - [CMake Configuration](#cmake-configuration)
  - [Function Traits](#function-traits)
  - [Output Type](#output-type)

# Environment

- CMake 3.31.3
- Visual Studio 17 2022
- MinGW 14.2.0
- Clang 19.1.6

# Project Content

## CMake Configuration

[cmake/README](./cmake/README.md)

I put my usual **CMake** configuration on both **Linux** and **Windows**. While this is common to most projects, I've also wrapped some useful cmake functions to help me build more complex projects, including these at the top of the config whenever possible.

For example, you can use the following code to include this configuration in your project:

```cmake
# Set the cmake module path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Import the relevant cmake configuration
include(compiler_settings)
include(copy_lib_interface_headers)
include(copy_dirs_if_diff)
include(auto_install_post_build)
include(generate_lib_exports_header)
```

## Function Traits

[functional/README](./utils/functional/README.md)

Function traits can extract function types to perform specific behaviors, such as extracting types from template functions to achieve implicit invocation of template functions; or extracting the parent class of a member function to use class pointers and function pointers as parameters.

- [function_traits](./utils/functional/function_traits.h)
  - Function traits, used to obtain function return values, parameter lists, etc., mainly used in templates
  - Currently tested to extract all function types: normal functions, function pointers, standard library functions, member functions.

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

More information can be found in this repository [supine0703/qt-settings](https://github.com/supine0703/qt-settings).

## Output Type

- [TypeName](./utils/type/cxx17/typename.h)
  - Use `TypeName<T>::value()` instead of `typeid(T).name()` to get the type name of a variable. Because `gcc`'s `typeid(T).name()` is difficult to observe and debug, this is more direct and convenient.
  - example:
    ```cpp
    TypeName<void (*)(size_t)>::value();  // return: void (*)(unsigned long long)
    ```

