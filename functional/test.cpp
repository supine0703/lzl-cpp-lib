/**
 * License: MIT
 * Copyright (c) 2024 Li Zonglin (李宗霖) github: <https://github.com/supine0703>
 * Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>
 */

#include "function_traits.h"
#include "lzl_logo.h"
#include "typename.h"

#include <iostream>
#include <string>

using namespace lzl::utils;

#define LZL_LOG_TYPE(T)                                                                            \
    do                                                                                             \
    {                                                                                              \
        std::cout << " " << #T << std::string(5 - (sizeof(#T) >> 3), '\t') << " : \t"              \
                  << TypeName<T>::value() << std::endl;                                            \
    } while (0)

#define LZL_LOG_X_TYPE(X)                                                                          \
    do                                                                                             \
    {                                                                                              \
        std::cout << " X: " << #X << std::string(5 - ((sizeof(#X) + 3) >> 3), '\t') << " : \t"     \
                  << TypeName(X).value() << std::endl;                                             \
    } while (0)


// int func(int a, std::string b);

// template <typename T>
// void printType()
// {
//     cout << typeid(T).name() << endl;
// }

// float (*cast_func)(int, int, int, int);
// float free_function(const std::string& a, int b)
// {
//     return (float)a.size() / b;
// }
// struct AA
// {
//     int f(int a, int b) volatile { return a + b; }
//     int operator()(int) const { return 0; }
// };

// 递归基函数
// template <typename Traits, size_t I = 0>
// void log_arg_type()
// {
//     if constexpr (I < Traits::arity)
//     {
//         using argN = typename Traits::template arg<I>::type;
//         std::cout << " typename traits::arg<" << I << ">"
//                   << std::string(5 - ((23 + std::to_string(I).size()) >> 3), '\t') << " : \t"
//                   << TypeName<argN>::value() << std::endl;
//         log_arg_type<Traits, I + 1>();
//     }
// }

template <typename T>
void test_function_traits()
{
    using traits = function_traits<T>;
    LZL_LOG_TYPE(typename traits::pointer);
    LZL_LOG_TYPE(typename traits::function_type);
    LZL_LOG_TYPE(typename traits::stl_function_type);
    LZL_LOG_TYPE(typename traits::return_type);
    LZL_LOG_TYPE(typename traits::args_tuple);
    // log_arg_type<traits>();
}

void test()
{
    std::cout << "=== Test Start! ===\n" << std::endl;

    // Ordinary function
    test_function_traits<void(double, const char*)>();
    using traits = function_traits<void(double, const char*)>;

    std::cout << "\n=== Test End! ===\n" << std::endl;

    auto l1 = []() {
    };
    auto l2 = []() {
        return 0;
    };
    auto l3 = [](int a, int b) {
        return a + b;
    };
    auto l4 = [](double a, double b) {
        return a + b;
    };
    LZL_LOG_TYPE(decltype(l1));
    LZL_LOG_TYPE(decltype(l2));
    LZL_LOG_TYPE(decltype(l3));
    LZL_LOG_TYPE(decltype(l4));
    // function
    struct f1
    {
        void operator()() {}
    };
    struct f2
    {
        int operator()() { return 0; }
    };
    struct f3
    {
        int operator()(int a, int b) { return a + b; }
    };
    struct f4
    {
        double operator()(double a, double b) { return a + b; }
    };
    LZL_LOG_TYPE(f1);
    LZL_LOG_TYPE(f2);
    LZL_LOG_TYPE(f3);
    LZL_LOG_TYPE(f3);
}

int main(int argc, char const* argv[])
{
    std::cout << "This is functional test, use cpp version: " << __CPP_VERSION << std::endl;
    std::cout << lzl::Logo::value << std::endl;
    test();
    return 0;
}
