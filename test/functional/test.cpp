/*******************************************************************************
**
** License: MIT
** Copyright (c) 2024-2025 李宗霖 (Li Zonglin)
** Email: supine0703@outlook.com
** GitHub: https://github.com/supine0703
** Repository: https://github.com/supine0703/lzl-cpp-lib
**
*******************************************************************************/

#include "lzl/function_traits.h"
#include "lzl/logo.h"
#include "lzl/typename.h"

#include <cstdint>
#include <functional>
#include <iostream>
#include <string>

using namespace lzl::utils;

#define LZL_LOG_TYPE(T)                                                               \
    do                                                                                \
    {                                                                                 \
        std::cout << " " << #T << std::string(5 - (sizeof(#T) >> 3), '\t') << " : \t" \
                  << TypeName<T>::value() << std::endl;                               \
    } while (0)

#define LZL_LOG_X_TYPE(X)                                                                      \
    do                                                                                         \
    {                                                                                          \
        std::cout << " X: " << #X << std::string(5 - ((sizeof(#X) + 3) >> 3), '\t') << " : \t" \
                  << TypeName(X).value() << std::endl;                                         \
    } while (0)

// 递归基函数
template <typename Traits, size_t I = 0>
void log_arg_type()
{
#if __cpp_if_constexpr
    if constexpr (I < Traits::arity)
    {
        using argN = typename Traits::template arg<I>::type;
        std::cout << " typename traits::arg<" << I << ">"
                  << std::string(5 - ((23 + std::to_string(I).size()) >> 3), '\t') << " : \t"
                  << TypeName<argN>::value() << std::endl;
        log_arg_type<Traits, I + 1>();
    }
#endif // __cpp_if_constexpr
}

template <typename T>
void test_function_traits()
{
    std::cout << "=== Test: " << TypeName<T>::value() << " ===" << std::endl;
    using traits = function_traits<T>;
    LZL_LOG_TYPE(typename traits::pointer);
    LZL_LOG_TYPE(typename traits::function_type);
    LZL_LOG_TYPE(typename traits::stl_function_type);
    LZL_LOG_TYPE(typename traits::return_type);
    LZL_LOG_TYPE(typename traits::args_tuple);
    log_arg_type<traits>();
    std::cout << std::endl;
}

template <typename T>
void test_function_traits(T)
{
    test_function_traits<T>();
}

void test()
{
    std::cout << "=== Test Start! ===\n" << std::endl;

    // Ordinary function
    test_function_traits<void(const char*)>();

    // Function pointer
    test_function_traits<int (*)(int, char, uint16_t, void*)>();

    // Function object
#if __cplusplus >= 201703L || _MSVC_LANG >= 201703L
    auto f = [](int, char, uint16_t, void*) -> int {
        return 0;
    };
    LZL_LOG_TYPE(function_traits<decltype(f)>::class_type);
    test_function_traits(std::function(f));
#else
    using ft = std::function<void(int)>;
    test_function_traits<ft>();
#endif
    // Lambda
    auto lambda = [](int a, char b, uint16_t c, void* d) -> int {
        return 0;
    };
    LZL_LOG_TYPE(function_traits<decltype(lambda)>::class_type);
    test_function_traits<decltype(lambda)>();
    // Member function
    struct AA
    {
        int f(int a, int b) volatile { return a + b; }
        int operator()(double) const { return 0; }
    };
    LZL_LOG_TYPE(function_traits<decltype(&AA::f)>::class_type);
    test_function_traits<int (AA::*)(int, int)>();
    test_function_traits<decltype(&AA::f)>();

    std::cout << "\n=== Test End! ===\n" << std::endl;
}

int main(int argc, char const* argv[])
{
    std::cout << "This is functional test, use cpp version: " << __CPP_VERSION << std::endl;
    std::cout << lzl::Logo::value << std::endl;
    test();
    return 0;
}
