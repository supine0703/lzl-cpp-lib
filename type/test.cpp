/**
 * License: MIT
 * Copyright (c) 2024 李宗霖 github: <https://github.com/supine0703>
 * Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>
 */

#include "lzl_logo.h"
#include "typename.h"

#include <cstdint>
#include <iostream>
#include <vector>

using namespace lzl::utils;

#define LZL_LOG_TYPE(T)                                                                            \
    do                                                                                             \
    {                                                                                              \
        std::cout << ' ' << #T << std::string(5 - (sizeof(#T) >> 3), '\t') << " : \t"              \
                  << TypeName<T>::value() << std::endl;                                            \
    } while (0)

void test()
{
    std::cout << "=== Test Start! ===\n" << std::endl;
    std::cout << " type(T)\t\t\t\t : \tTypeName<T>::value()" << std::endl;
    std::cout << "================================================================================"
              << std::endl;
    LZL_LOG_TYPE(int);
    LZL_LOG_TYPE(const int32_t);
    LZL_LOG_TYPE(volatile int);
    LZL_LOG_TYPE(const volatile int);
    LZL_LOG_TYPE(uint64_t*);
    LZL_LOG_TYPE(uint64_t* const);
    LZL_LOG_TYPE(size_t&);
    LZL_LOG_TYPE(volatile size_t&);
    LZL_LOG_TYPE(std::size_t&&);
    LZL_LOG_TYPE(const volatile std::size_t&&);
    using pair1 = std::pair<int, double>;
    LZL_LOG_TYPE(pair1);
    using tuple1 = std::tuple<int, double, const char*>;
    LZL_LOG_TYPE(tuple1);
    LZL_LOG_TYPE(void (*)(int));
    struct AAA
    {
    };
    LZL_LOG_TYPE(int(AAA::*)(void (*)(int)));
    LZL_LOG_TYPE(int(AAA::*)(int, double));
    LZL_LOG_TYPE(int(AAA::*)(int, const char*) const);
    LZL_LOG_TYPE(int(AAA::*)(int, std::string) volatile);
    LZL_LOG_TYPE(int(AAA::*)(float) const volatile);
    LZL_LOG_TYPE(int(AAA::*)() const volatile);
    using func1 = std::function<void(int, double, const volatile char&)>;
    LZL_LOG_TYPE(func1);
    using func2 = std::function<void(int, double, const volatile char&)>&;
    LZL_LOG_TYPE(func2);
    using func3 = std::function<void(int, double, const volatile char&)>&&;
    LZL_LOG_TYPE(func3);
    using func4 = std::function<void(int, double, const volatile char&)> const*;
    LZL_LOG_TYPE(func4);
    using enum1 = enum SS : size_t {
        A,
        B,
    };
    LZL_LOG_TYPE(enum1);
    using enum2 = enum class FF : bool {
    };
    LZL_LOG_TYPE(enum2);
    LZL_LOG_TYPE(AAA[10]);
    LZL_LOG_TYPE(std::vector<SS>);

    std::cout << "\n=== Test End! ===\n" << std::endl;
}

int main(int argc, char const* argv[])
{
    std::cout << "This is type test, use cpp version: " << __CPP_VERSION << std::endl;
    std::cout << lzl::Logo::value << std::endl;
    test();
    return 0;
}
