/**
 * License: MIT
 * Copyright (c) 2024 李宗霖 github: <https://github.com/supine0703>
 * Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>
 */

/**
 * TypeNameDemangle -> TypeName: 
 *   Start thinking Demangle, but it seems better to implement typename directly?
 * @file: typename.h
 * @brief: make type to string name
 * @example: TypeName<void (*)(size_t)>::value();  // return: void (*)(unsigned long long)
 * @cpp: c++11 can be used but it is better to use c++17 or higher
 */

#ifndef LZL_TYPENAME_DEMANGLE_H
#define LZL_TYPENAME_DEMANGLE_H

#include <functional>
#include <string>

namespace lzl::utils {

template <typename T, typename Enable = void>
struct TypeName
{
    static constexpr std::string value()
    {
#if 0
        return typeid(T).name();
#else
        std::string name = typeid(T).name();
        auto pos = name.find_last_of("0123456789");
        return (pos != std::string::npos) ? name.substr(pos + 1) : name;
#endif
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
        auto pos = name.find_last_of("0123456789");
        name = (pos != std::string::npos) ? name.substr(pos + 1) : name;
#endif
        return (
            std::string("enum<") + TypeName<typename std::underlying_type<T>::type>::value() +
            ">(" + name + ")"
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
    static std::string value()
    {
        return std::string("const volatile ") + TypeName<T>::value() + "*";
    }
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
    static std::string value()
    {
        return std::string("const volatile ") + TypeName<T>::value() + "&";
    }
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
    static std::string value()
    {
        return std::string("const volatile ") + TypeName<T>::value() + "&&";
    }
};

// array
template <typename T, size_t N>
struct TypeName<T[N]>
{
    static std::string value()
    {
        return std::string(TypeName<T>::value()) + "[" + std::to_string(N) + "]";
    }
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
};
#endif // __cpp_if_constexpr

// usual stl container
// std::string
template <>
struct TypeName<std::string>
{
    static std::string value() { return "std::string"; }
};

// std::vector
#if __cpp_if_constexpr
template <typename T>
struct TypeName<std::vector<T>>
{
    static std::string value() { return std::string("std::vector<") + TypeName<T>::value() + ">"; }
};
#endif // __cpp_if_constexpr

// ... ... more

} // namespace lzl::utils

#endif // LZL_TYPENAME_DEMANGLE_H
