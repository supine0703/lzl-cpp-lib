/**
 * License: MIT
 * Copyright (c) 2024 李宗霖 github: <https://github.com/supine0703>
 * Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>
 */

#include "function_traits.h"
#include "lzl_logo.h"
#include "typename.h"

#include <iostream>
#include <string>

using namespace lzl::utils;

#define LZL_LOG_TYPE(T) std::cout << #T << ": " << typeid(T).name() << std::endl

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

struct AACC
{
    void t(int a) {}
    void ttt(int a, double b, const volatile char& c) {}
};

void test()
{
    std::cout << "=== Test Start! ===\n" << std::endl;
    using traits = function_traits<void(const int, double, const volatile char&)>;
    static_assert(traits::arity == 3, "Arity should be 3");
    // 访问每个参数的类型
    using t = traits::args_tuple;
    using arg0_type = traits::arg<0>::type; // int
    using arg1_type = traits::arg<1>::type; // double
    using arg2_type = traits::arg<2>::type; // const char*
    std::cout << "args_tuple: " << TypeName<t>::value() << std::endl;
    std::cout << "arg0_type: " << TypeName<arg0_type>::value() << std::endl;
    std::cout << "arg1_type: " << TypeName<arg1_type>::value() << std::endl;
    std::cout << "arg2_type: " << TypeName<arg2_type>::value() << std::endl;
    // using arg3_type = traits::arg<3>::type; // compile error
    using t1 = traits::function_type;
    using t2 = traits::pointer;
    std::cout << "function_type: " << TypeName<t1>::value() << std::endl;
    std::cout << "pointer: " << TypeName<t2>::value() << std::endl;

    using traits2 = function_traits<decltype(&AACC::t)>;
    using t3 = traits2::args_tuple;
    using arg0_type2 = traits2::arg<0>::type; // int
    std::cout << "\n\nargs_tuple: " << TypeName<t3>::value() << std::endl;
    std::cout << "arg0_type: " << TypeName<arg0_type2>::value() << std::endl;
    using t4 = traits2::function_type;
    using t5 = traits2::pointer;
    std::cout << "function_type: " << TypeName<t4>::value() << std::endl;
    std::cout << "pointer: " << TypeName<t5>::value() << std::endl;
    std::cout << "\n=== Test End! ===\n" << std::endl;
}

int main(int argc, char const* argv[])
{
    std::cout << "This is functional test, use cpp version: " << __CPP_VERSION << std::endl;
    std::cout << lzl::Logo::value << std::endl;
    test();

    return 0;
}
