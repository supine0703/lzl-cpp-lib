/*******************************************************************************
**
** License: MIT
** Copyright (c) 2024-2025 李宗霖 (Li Zonglin)
** Email: supine0703@outlook.com
** GitHub: https://github.com/supine0703
** Repository: https://github.com/supine0703/lzl-cpp-lib
**
*******************************************************************************/

#include "lzl/logo.h"
#include "lzl/typename.h"

#include <cstdint>
#include <iostream>
#include <vector>

using namespace lzl::utils;

#define LZL_LOG_TYPE(T)                                                               \
    do                                                                                \
    {                                                                                 \
        std::cout << " " << #T << std::string(5 - (sizeof(#T) >> 3), '\t') << " : \t" \
                  << TypeName<T>::value() << std::endl;                               \
    } while (0)

#if __CPP_VERSION >= 201703L
    #define LZL_LOG_X_TYPE(X)                                                                      \
        do                                                                                         \
        {                                                                                          \
            std::cout << " X: " << #X << std::string(5 - ((sizeof(#X) + 3) >> 3), '\t') << " : \t" \
                      << TypeName(X).value() << std::endl;                                         \
        } while (0)
#else
    #define LZL_LOG_X_TYPE(X)                                                             \
        do                                                                                \
        {                                                                                 \
            std::cout << " " << #X << std::string(5 - (sizeof(#X) >> 3), '\t') << " : \t" \
                      << TypeName<decltype(X)>::value() << std::endl;                     \
        } while (0)
#endif

void test()
{
    std::cout << "=== Test Start! ===\n" << std::endl;
    std::cout << " type(T)\t\t\t\t : \tTypeName<T>::value()" << std::endl;
    std::cout << "================================================================================"
              << std::endl;

    // basic type(pointer, reference, const, volatile)
    std::cout << "\n=== basic type (pointer, reference, const, volatile) ===" << std::endl;
    const float f_num = 0.0f;
    LZL_LOG_X_TYPE(0ULL);
    LZL_LOG_X_TYPE(f_num);
    LZL_LOG_TYPE(volatile int);
    LZL_LOG_TYPE(const volatile int);
    LZL_LOG_X_TYPE(&f_num);
    LZL_LOG_TYPE(uint64_t* const);
    auto&& lrf_num = f_num;
    auto&& rrf_num = std::move(f_num);
    LZL_LOG_X_TYPE(lrf_num);
    LZL_LOG_TYPE(volatile size_t&);
    LZL_LOG_X_TYPE(rrf_num);
    LZL_LOG_TYPE(const volatile std::size_t&&);

    // pair & tuple
    std::cout << "\n=== pair & tuple ===" << std::endl;
    using pair1 = std::pair<int, double>;
    LZL_LOG_TYPE(pair1);
    using tuple1 = std::tuple<int, double, const char*>;
    LZL_LOG_TYPE(tuple1);
    struct _P
    {
        int a;
        double b;
    } _p;

    // struct <-> pair
    std::cout << "\n=== struct <-> pair ===" << std::endl;
    LZL_LOG_TYPE(_P);
    LZL_LOG_X_TYPE(_p);
    LZL_LOG_X_TYPE(std::move(_p));
    std::cout << typeid(_p).name() << std::endl;
    std::cout << typeid(std::move(_p)).name() << std::endl;

    // function (pointer, std::function, member, lambda)
    std::cout << "\n=== function (pointer, std::function, member, lambda) ===" << std::endl;
    LZL_LOG_TYPE(void(int));
    const float (*const ptr)(size_t) = nullptr;
    LZL_LOG_X_TYPE(ptr);
    using func1 = std::function<void(const volatile char&)>;
    LZL_LOG_TYPE(func1);
    using func2 = std::function<void(const volatile char**)>&&;
    LZL_LOG_TYPE(func2);
    using func3 = std::function<void(const char*** const, int)> const*;
    LZL_LOG_TYPE(func3);
    struct AAA
    {
        void func(int) const {}
    };
    LZL_LOG_TYPE(size_t(AAA::*)(double (*)(int)));
    LZL_LOG_X_TYPE(&AAA::func);
    LZL_LOG_TYPE(int(AAA::*)(int, std::string) volatile);
    LZL_LOG_TYPE(int(AAA::*)() const volatile);
    auto lambda = [&_p](int) {
        return _p;
    };
    LZL_LOG_X_TYPE(lambda);
#if __cpp_concepts
    auto lambda2 = [](auto i) {
    };
    LZL_LOG_X_TYPE(lambda2);
    LZL_LOG_X_TYPE([](int) { return 0.0; });
    LZL_LOG_TYPE(decltype([](int) { return 0.0; }));
#endif // __cpp_concept; c++20
    struct La
    {
        auto operator()(int) -> double { return 0.0; }
    } la;
    LZL_LOG_TYPE(La);

    // enum & array & vector
    std::cout << "\n=== enum & array & vector ===" << std::endl;
    using enum1 = enum SS : size_t {
        A,
        B,
    };
    LZL_LOG_TYPE(enum1);
    using enum2 = enum class FF : bool {
    };
    LZL_LOG_TYPE(enum2);
    enum2 ee;
    LZL_LOG_X_TYPE(ee);
    LZL_LOG_TYPE(AAA[10]);
    int arr[10];
    LZL_LOG_X_TYPE(arr);
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
