/*******************************************************************************
**
** License: MIT
** Copyright (c) 2024-2025 李宗霖 (Li Zonglin)
** Email: supine0703@outlook.com
** GitHub: https://github.com/supine0703
** Repository: https://github.com/supine0703/lzl-cpp-lib
**
*******************************************************************************/

/**
 * TypeNameDemangle -> TypeName: 
 *   Start thinking Demangle, but it seems better to implement typename directly?
 * @file: typename.h
 * @brief: make type to string name
 * @example: TypeName<void (*)(size_t)>::value();  // return: void (*)(unsigned long long)
 * @cpp: c++11 can be used but it is better to use c++17 or higher
 *       because of `if constexpr` and `fold expression`, it can used by function...
 */

/**
 * @anchor Li Zonglin (李宗霖)　,，
 * @date 2024-10-27
 * Constructors are added to derive types from parameter variables
 * @date 2024-10-28
 * But, It must c++17 or higher can be used
 * @example: TypeName(123.456).value() // c++17 return: "double"; c++14 compile error
 */

/**
 * @anchor Li Zonglin (李宗霖)
 * @date 2024-10-28
 * I didn't find a perfect way to judge lambda, so I decided not to make lambda specialization
 */

/**
 * @anchor Li Zonglin (李宗霖)
 * @date 2024-10-29
 * I found that lambda can be judged by whether `typeid` and `operator()` are available. 
 * Based on `GCC`, `Clang`, and `MSVC`, there is a high probability of no problem.
 */

#ifndef LZL_TYPE_TYPENAME_H
#define LZL_TYPE_TYPENAME_H

#include "maybe_lambda.h"

#include <functional>

#define LZL_TYPENAME_NOT_LAMBDA 0

namespace lzl {
namespace utils {

// Helper function template to handle type name concatenation in tuples
template <typename... Args>
struct concat;

// ...
#if LZL_TYPENAME_NOT_LAMBDA
template <typename T, typename = void>
struct TypeName
{
    static constexpr const char* value() { return typeid(T).name(); }
};
#else
template <typename T, typename = void>
struct TypeName
{
private:
    // ToCallOperatorType
    template <typename U, typename = void>
    struct ToCallOperatorType
    {
        using type = U;
    };

    template <typename U>
    struct ToCallOperatorType<U, typename std::enable_if<has_call_operator<U>::value>::type>
    {
        using type = decltype(&U::operator());
    };

    // LambdaTypeName
    template <typename Lambda>
    struct LambdaTypeName
    {
        static std::string value() { return ""; }
    };

    // LambdaTypeName specialization
    template <typename Ret, typename Class, typename... Args>
    struct LambdaTypeName<Ret (Class::*)(Args...) const>
    {
        static std::string value()
        {
            if (sizeof...(Args) == 0)
            {
                return std::string("(void) -> ") + TypeName<Ret>::value();
            }
            else
            {
                return std::string("(") + concat<Args...>::value() + ") -> " + TypeName<Ret>::value();
            }
        }
    };

public:
    static std::string value()
    {
        if (!maybe_lambda<T>::value())
        {
            return typeid(T).name();
        }
        // lambda
        return (std::string("lambda<") + LambdaTypeName<typename ToCallOperatorType<T>::type>::value() + ">");
    }
};
#endif
template <>
struct concat<>
{
    static std::string value() { return ""; }
};

template <typename T, typename... Args>
struct concat<T, Args...>
{
    static std::string value()
    {
        return std::string(TypeName<T>::value()) + (sizeof...(Args) > 0 ? ", " : "")
               + concat<Args...>::value();
    }
};

// enum ...
template <typename T>
// Compatible with c++11
struct TypeName<T, typename std::enable_if<std::is_enum<T>::value>::type>
{
    static std::string value()
    {
        std::string name = typeid(T).name();
#if 0
#else
        name = typeid(T).name();
        auto pos = name.find_last_of("0123456789:");
        name = (pos != std::string::npos) ? name.substr(pos + 1) : name;
#endif
        return (
            std::string("enum<") + TypeName<typename std::underlying_type<T>::type>::value() + "> " + name
        );
    }
};

// basic type
template <>
struct TypeName<void>
{
    static constexpr const char* value() { return "void"; }
};

template <>
struct TypeName<bool>
{
    static constexpr const char* value() { return "bool"; }
};

template <>
struct TypeName<char>
{
    static constexpr const char* value() { return "char"; }
};

template <>
struct TypeName<unsigned char>
{
    static constexpr const char* value() { return "unsigned char"; }
};

template <>
struct TypeName<short>
{
    static constexpr const char* value() { return "short"; }
};

template <>
struct TypeName<unsigned short>
{
    static constexpr const char* value() { return "unsigned short"; }
};

template <>
struct TypeName<int>
{
    static constexpr const char* value() { return "int"; }
};

template <>
struct TypeName<unsigned int>
{
    static constexpr const char* value() { return "unsigned int"; }
};

template <>
struct TypeName<long>
{
    static constexpr const char* value() { return "long"; }
};

template <>
struct TypeName<unsigned long>
{
    static constexpr const char* value() { return "unsigned long"; }
};

template <>
struct TypeName<long long>
{
    static constexpr const char* value() { return "long long"; }
};

template <>
struct TypeName<unsigned long long>
{
    static constexpr const char* value() { return "unsigned long long"; }
};

template <>
struct TypeName<float>
{
    static constexpr const char* value() { return "float"; }
};

template <>
struct TypeName<double>
{
    static constexpr const char* value() { return "double"; }
};

// const, volatile ...
template <typename T>
struct TypeName<const T>
{
    static std::string value() { return std::string("const ") + TypeName<T>::value(); }
};

template <typename T>
struct TypeName<volatile T>
{
    static std::string value() { return std::string("volatile ") + TypeName<T>::value(); }
};

template <typename T>
struct TypeName<const volatile T>
{
    static std::string value() { return std::string("const volatile ") + TypeName<T>::value(); }
};

// pointer
template <typename T>
struct TypeName<T*>
{
    static std::string value() { return std::string(TypeName<T>::value()) + "*"; }
};

template <typename T>
struct TypeName<const T*>
{
    static std::string value() { return std::string("const ") + TypeName<T>::value() + "*"; }
};

template <typename T>
struct TypeName<volatile T*>
{
    static std::string value() { return std::string("volatile ") + TypeName<T>::value() + "*"; }
};

template <typename T>
struct TypeName<const volatile T*>
{
    static std::string value() { return std::string("const volatile ") + TypeName<T>::value() + "*"; }
};

// lvalue reference
template <typename T>
struct TypeName<T&>
{
    static std::string value() { return TypeName<T>::value() + std::string("&"); }
};

template <typename T>
struct TypeName<const T&>
{
    static std::string value() { return std::string("const ") + TypeName<T>::value() + "&"; }
};

template <typename T>
struct TypeName<volatile T&>
{
    static std::string value() { return std::string("volatile ") + TypeName<T>::value() + "&"; }
};

template <typename T>
struct TypeName<const volatile T&>
{
    static std::string value() { return std::string("const volatile ") + TypeName<T>::value() + "&"; }
};

// rvalue reference
template <typename T>
struct TypeName<T&&>
{
    static std::string value() { return TypeName<T>::value() + std::string("&&"); }
};

template <typename T>
struct TypeName<const T&&>
{
    static std::string value() { return std::string("const ") + TypeName<T>::value() + "&&"; }
};

template <typename T>
struct TypeName<volatile T&&>
{
    static std::string value() { return std::string("volatile ") + TypeName<T>::value() + "&&"; }
};

template <typename T>
struct TypeName<const volatile T&&>
{
    static std::string value() { return std::string("const volatile ") + TypeName<T>::value() + "&&"; }
};

// array
template <typename T, size_t N>
struct TypeName<T[N]>
{
    static std::string value() { return std::string(TypeName<T>::value()) + "[" + std::to_string(N) + "]"; }
};

// pair
template <typename T1, typename T2>
struct TypeName<std::pair<T1, T2>>
{
    static std::string value()
    {
        return (std::string("std::pair<") + TypeName<T1>::value() + ", " + TypeName<T2>::value() + ">");
    }
};

// tuple
template <>
struct TypeName<std::tuple<>>
{
    static std::string value() { return "std::tuple<>"; }
};

template <typename... Args>
struct TypeName<std::tuple<Args...>>
{
    static std::string value() { return std::string("std::tuple<") + concat<Args...>::value() + ">"; }
};

// function
template <typename Ret, typename... Args>
struct TypeName<Ret(Args...)>
{
    static std::string value()
    {
        return std::string(TypeName<Ret>::value()) + "(" + concat<Args...>::value() + ")";
    }
};

// function pointer
template <typename Ret, typename... Args>
struct TypeName<Ret (*)(Args...)>
{
    static std::string value()
    {
        return std::string(TypeName<Ret>::value()) + " (*)(" + concat<Args...>::value() + ")";
    }
};

// std::function
template <typename Ret, typename... Args>
struct TypeName<std::function<Ret(Args...)>>
{
    static std::string value()
    {
        return (
            std::string("std::function<") + TypeName<Ret>::value() + "(" + concat<Args...>::value() + ")>"
        );
    }
};

// member function (const, volatile)
template <typename Ret, typename Class, typename... Args>
struct TypeName<Ret (Class::*)(Args...)>
{
    static std::string value()
    {
        return (
            std::string(TypeName<Ret>::value()) + "(" + TypeName<Class>::value() + "::*)("
            + concat<Args...>::value() + ")"
        );
    }
};

template <typename Ret, typename Class, typename... Args>
struct TypeName<Ret (Class::*)(Args...) const>
{
    static std::string value()
    {
        return (
            std::string(TypeName<Ret>::value()) + "(" + TypeName<Class>::value() + "::*)("
            + concat<Args...>::value() + ") const"
        );
    }
};

template <typename Ret, typename Class, typename... Args>
struct TypeName<Ret (Class::*)(Args...) volatile>
{
    static std::string value()
    {
        return (
            std::string(TypeName<Ret>::value()) + "(" + TypeName<Class>::value() + "::*)("
            + concat<Args...>::value() + ") volatile"
        );
    }
};
template <typename Ret, typename Class, typename... Args>
struct TypeName<Ret (Class::*)(Args...) const volatile>
{
    static std::string value()
    {
        return (
            std::string(TypeName<Ret>::value()) + "(" + TypeName<Class>::value() + "::*)("
            + concat<Args...>::value() + ") const volatile"
        );
    }
};

// usual stl container
// std::string
template <>
struct TypeName<std::string>
{
    static std::string value() { return "std::string"; }
};

// ... ... more

} // namespace utils
} // namespace lzl

#endif // LZL_TYPE_TYPENAME_H
