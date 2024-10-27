/**
 * License: MIT
 * Copyright (c) 2024 Li Zonglin (李宗霖) github: <https://github.com/supine0703>
 * Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>
 */

#include "is_lambda.h"
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
    // basic type (pointer, reference, const, volatile)
    const float f = 1.1;
    std::cout << TypeName(&f).value() << "!!!" << std::endl;
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
    // pair & tuple
    using pair1 = std::pair<int, double>;
    LZL_LOG_TYPE(pair1);
    using tuple1 = std::tuple<int, double, const char*>;
    LZL_LOG_TYPE(tuple1);
    // function (pointer, member, lambda, std::function)
    LZL_LOG_TYPE(void(int));
    LZL_LOG_TYPE(void (*)(int));
    struct AAA
    {
        void func(int) const {}
    };
    std::cout << TypeName(&AAA::func).value() << "!!!" << std::endl;
    LZL_LOG_TYPE(int(AAA::*)(void (*)(int)));
    LZL_LOG_TYPE(int(AAA::*)(int, double));
    LZL_LOG_TYPE(int(AAA::*)(int, const char*) const);
    LZL_LOG_TYPE(int(AAA::*)(int, std::string) volatile);
    LZL_LOG_TYPE(int(AAA::*)(float) const volatile);
    LZL_LOG_TYPE(int(AAA::*)() const volatile);
    auto lambda = [&f](int) {
        return f;
    };
    std::cout << TypeName([]() { return 0; }).value() << "!!!" << std::endl;
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

    std::decay_t<decltype([]() {})> a;

    struct Ul
    {
        double operator()(int i) const
        {
            std::cout << i << std::endl;
            return 0.0;
        }
    };

    using lambda1 = decltype([](int) -> double { return 0.0; });
    using lambda2 = std::decay_t<decltype([](int) -> double { return 0.0; })>;
    std::cout << std::is_same_v<
                     lambda2,
                     Ul> << std::is_same_v<lambda1, lambda2> << std::is_same_v<Ul, std::decay_t<Ul>>

              << std::endl;

    LZL_LOG_TYPE(lambda1);
    LZL_LOG_TYPE(lambda2);
    LZL_LOG_TYPE(Ul);

    std::cout << typeid(lambda1).name() << std::endl;
    std::cout << typeid(std::decay_t<lambda1>).name() << std::endl;
    std::cout << typeid(Ul).name() << std::endl;
    std::cout << typeid(std::decay_t<Ul>).name() << std::endl;
}

int main(int argc, char const* argv[])
{
    std::cout << "This is type test, use cpp version: " << __CPP_VERSION << std::endl;
    std::cout << lzl::Logo::value << std::endl;
    test();
    return 0;
}
