/**
 * License: MIT
 * Copyright (c) 2024 Li Zonglin (李宗霖) github: <https://github.com/supine0703>
 * Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>
 */

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

#ifndef LZL_TYPE_TYPENAME_H
#define LZL_TYPE_TYPENAME_H

#include "c++11/maybe_lambda.h"
#include "maybe_lambda.h"

#include <functional>
#include <string>


namespace lzl {
namespace utils {

template <typename T, typename Enable = void>
struct TypeName
{
    static std::string value()
    {
#if 0
        return typeid(T).name();
#else
        std::string name = typeid(T).name();
        if constexpr (has_call_operator<T>::value)
        {
            if (maybe_lambda<T>::value())
            {
                return std::string("lambda<") + LambdaTypeName<decltype(&T::operator())>::value() +
                       ">";
            }
        }
        return name;
#endif
    }

    TypeName(const T&) {}
    TypeName(T&&) {}

private:
    template <typename Lambda>
    struct LambdaTypeName
    {
        static std::string value() { return ""; }
    };

    template <typename Ret, typename Class, typename... Args>
    struct LambdaTypeName<Ret (Class::*)(Args...) const>
    {
        static std::string value()
        {
            if constexpr (sizeof...(Args) == 0)
            {
                return "(void) -> " + std::string(TypeName<Ret>::value());
            }
            else
            {
                return (
                    std::string("(") + (... + (std::string(TypeName<Args>::value()) + ", ")) +
                    "\b\b) -> " + TypeName<Ret>::value()
                );
            }
        }
    };
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
            std::string("enum<") + TypeName<typename std::underlying_type<T>::type>::value() +
            "> " + name
        );
    }

    TypeName(const T&) {}
    TypeName(T&&) {}
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

    TypeName(bool) {}
};

template <>
struct TypeName<char>
{
    static constexpr const char* value() { return "char"; }

    TypeName(char) {}
};

template <>
struct TypeName<unsigned char>
{
    static constexpr const char* value() { return "unsigned char"; }

    TypeName(unsigned char) {}
};

template <>
struct TypeName<short>
{
    static constexpr const char* value() { return "short"; }

    TypeName(short) {}
};

template <>
struct TypeName<unsigned short>
{
    static constexpr const char* value() { return "unsigned short"; }

    TypeName(unsigned short) {}
};

template <>
struct TypeName<int>
{
    static constexpr const char* value() { return "int"; }

    TypeName(int) {}
};

template <>
struct TypeName<unsigned int>
{
    static constexpr const char* value() { return "unsigned int"; }

    TypeName(unsigned int) {}
};

template <>
struct TypeName<long>
{
    static constexpr const char* value() { return "long"; }

    TypeName(long) {}
};

template <>
struct TypeName<unsigned long>
{
    static constexpr const char* value() { return "unsigned long"; }

    TypeName(unsigned long) {}
};

template <>
struct TypeName<long long>
{
    static constexpr const char* value() { return "long long"; }

    TypeName(long long) {}
};

template <>
struct TypeName<unsigned long long>
{
    static constexpr const char* value() { return "unsigned long long"; }

    TypeName(unsigned long long) {}
};

template <>
struct TypeName<float>
{
    static constexpr const char* value() { return "float"; }

    TypeName(float) {}
};

template <>
struct TypeName<double>
{
    static constexpr const char* value() { return "double"; }

    TypeName(double) {}
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

    TypeName(T*) {}
};

template <typename T>
struct TypeName<const T*>
{
    static std::string value() { return std::string("const ") + TypeName<T>::value() + "*"; }

    TypeName(const T*) {}
};

template <typename T>
struct TypeName<volatile T*>
{
    static std::string value() { return std::string("volatile ") + TypeName<T>::value() + "*"; }

    TypeName(volatile T*) {}
};

template <typename T>
struct TypeName<const volatile T*>
{
    static std::string value()
    {
        return std::string("const volatile ") + TypeName<T>::value() + "*";
    }

    TypeName(const volatile T*) {}
};

// lvalue reference
template <typename T>
struct TypeName<T&>
{
    static std::string value() { return TypeName<T>::value() + std::string("&"); }

    TypeName(T&) {}
};

template <typename T>
struct TypeName<const T&>
{
    static std::string value() { return std::string("const ") + TypeName<T>::value() + "&"; }

    TypeName(const T&) {}
};

template <typename T>
struct TypeName<volatile T&>
{
    static std::string value() { return std::string("volatile ") + TypeName<T>::value() + "&"; }

    TypeName(volatile T&) {}
};

template <typename T>
struct TypeName<const volatile T&>
{
    static std::string value()
    {
        return std::string("const volatile ") + TypeName<T>::value() + "&";
    }

    TypeName(const volatile T&) {}
};

// rvalue reference
template <typename T>
struct TypeName<T&&>
{
    static std::string value() { return TypeName<T>::value() + std::string("&&"); }

    TypeName(T&&) {}
};

template <typename T>
struct TypeName<const T&&>
{
    static std::string value() { return std::string("const ") + TypeName<T>::value() + "&&"; }

    TypeName(const T&&) {}
};

template <typename T>
struct TypeName<volatile T&&>
{
    static std::string value() { return std::string("volatile ") + TypeName<T>::value() + "&&"; }

    TypeName(volatile T&&) {}
};

template <typename T>
struct TypeName<const volatile T&&>
{
    static std::string value()
    {
        return std::string("const volatile ") + TypeName<T>::value() + "&&";
    }

    TypeName(const volatile T&&) {}
};

// array
template <typename T, size_t N>
struct TypeName<T[N]>
{
    static std::string value()
    {
        return std::string(TypeName<T>::value()) + "[" + std::to_string(N) + "]";
    }

    TypeName(T (&)[N]) {}
};

// pair
template <typename T1, typename T2>
struct TypeName<std::pair<T1, T2>>
{
    static std::string value()
    {
        return (
            std::string("std::pair<") + TypeName<T1>::value() + ", " + TypeName<T2>::value() + ">"
        );
    }

    TypeName(const std::pair<T1, T2>&) {}
};

#if __cpp_if_constexpr // c++17 : `if constexpr` and `fold expression`
// tuple
template <typename... Args>
struct TypeName<std::tuple<Args...>>
{
    static std::string value()
    {
        if constexpr (sizeof...(Args) == 0)
        {
            return "std::tuple<>";
        }
        else
        {
            return (
                std::string("std::tuple<") + (... + (std::string(TypeName<Args>::value()) + ", ")) +
                "\b\b>"
            );
        }
    }

    TypeName(const std::tuple<Args...>&) {}
};

// function
template <typename Ret, typename... Args>
struct TypeName<Ret(Args...)>
{
    static std::string value()
    {
        if constexpr (sizeof...(Args) == 0)
        {
            return std::string(TypeName<Ret>::value()) + "(void)";
        }
        else
        {
            return (
                std::string(TypeName<Ret>::value()) + "(" +
                (... + (std::string(TypeName<Args>::value()) + ", ")) + "\b\b)"
            );
        }
    }

    TypeName(Ret (*)(Args...)) {}
};

// function pointer
template <typename Ret, typename... Args>
struct TypeName<Ret (*)(Args...)>
{
    static std::string value()
    {
        if constexpr (sizeof...(Args) == 0)
        {
            return std::string(TypeName<Ret>::value()) + " (*)(void)";
        }
        else
        {
            return (
                std::string(TypeName<Ret>::value()) + " (*)(" +
                (... + (std::string(TypeName<Args>::value()) + ", ")) + "\b\b)"
            );
        }
    }

    TypeName(Ret (*)(Args...)) {}
};

// std::function
template <typename Ret, typename... Args>
struct TypeName<std::function<Ret(Args...)>>
{
    static std::string value()
    {
        if constexpr (sizeof...(Args) == 0)
        {
            return std::string("std::function<") + TypeName<Ret>::value() + "(void)>";
        }
        else
        {
            return (
                std::string("std::function<") + TypeName<Ret>::value() + "(" +
                (... + (std::string(TypeName<Args>::value()) + ", ")) + "\b\b)>"
            );
        }
    }

    TypeName(const std::function<Ret(Args...)>&) {}
};

// member function
template <typename Ret, typename Class, typename... Args>
struct TypeName<Ret (Class::*)(Args...)>
{
    static std::string value()
    {
        if constexpr (sizeof...(Args) == 0)
        {
            return (
                std::string(TypeName<Ret>::value()) + "(" + TypeName<Class>::value() + "::*)(void)"
            );
        }
        else
        {
            return (
                std::string(TypeName<Ret>::value()) + "(" + TypeName<Class>::value() + "::*)(" +
                (... + (std::string(TypeName<Args>::value()) + ", ")) + "\b\b)"
            );
        }
    }

    TypeName(Ret (Class::*)(Args...)) {}
};

template <typename Ret, typename Class, typename... Args>
struct TypeName<Ret (Class::*)(Args...) const>
{
    static std::string value()
    {
        if constexpr (sizeof...(Args) == 0)
        {
            return (
                std::string(TypeName<Ret>::value()) + "(" + TypeName<Class>::value() +
                "::*)(void) const"
            );
        }
        else
        {
            return (
                std::string(TypeName<Ret>::value()) + "(" + TypeName<Class>::value() + "::*)(" +
                (... + (std::string(TypeName<Args>::value()) + ", ")) + "\b\b) const"
            );
        }
    }

    TypeName(Ret (Class::*)(Args...) const) {}
};

template <typename Ret, typename Class, typename... Args>
struct TypeName<Ret (Class::*)(Args...) volatile>
{
    static std::string value()
    {
        if constexpr (sizeof...(Args) == 0)
        {
            return (
                std::string(TypeName<Ret>::value()) + "(" + TypeName<Class>::value() +
                "::*)(void) volatile"
            );
        }
        else
        {
            return (
                std::string(TypeName<Ret>::value()) + "(" + TypeName<Class>::value() + "::*)(" +
                (... + (std::string(TypeName<Args>::value()) + ", ")) + "\b\b) volatile"
            );
        }
    }

    TypeName(Ret (Class::*)(Args...) volatile) {}
};

template <typename Ret, typename Class, typename... Args>
struct TypeName<Ret (Class::*)(Args...) const volatile>
{
    static std::string value()
    {
        if constexpr (sizeof...(Args) == 0)
        {
            return (
                std::string(TypeName<Ret>::value()) + "(" + TypeName<Class>::value() +
                "::*)(void) const volatile"
            );
        }
        else
        {
            return (
                std::string(TypeName<Ret>::value()) + "(" + TypeName<Class>::value() + "::*)(" +
                (... + (std::string(TypeName<Args>::value()) + ", ")) + "\b\b) const volatile"
            );
        }
    }

    TypeName(Ret (Class::*)(Args...) const volatile) {}
};

#endif // __cpp_if_constexpr

// lambda
// ... ...

// usual stl container
// std::string
template <>
struct TypeName<std::string>
{
    static std::string value() { return "std::string"; }

    TypeName(const std::string&) {}
};

// std::vector
#if __cpp_if_constexpr // c++17 : 之后某个头文件包含了 `vector`

template <typename T>
struct TypeName<std::vector<T>>
{
    static std::string value() { return std::string("std::vector<") + TypeName<T>::value() + ">"; }

    TypeName(const std::vector<T>&) {}
};

#endif // __cpp_if_constexpr

// ... ... more

} // namespace utils
} // namespace lzl

#endif // LZL_TYPE_TYPENAME_H
