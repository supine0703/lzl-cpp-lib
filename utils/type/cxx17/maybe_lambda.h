/*******************************************************************************
**
** License: MIT
** Copyright (c) 2024-2025 李宗霖 (Li Zonglin)
** Email: supine0703@outlook.com
** GitHub: https://github.com/supine0703
** Repository: https://github.com/supine0703/lzl-cpp-lib
**
*******************************************************************************/

#ifndef LZL_TYPE_MAYBE_LAMBDA_H
#define LZL_TYPE_MAYBE_LAMBDA_H

#include <string>
#include <type_traits>
#include <typeinfo>

namespace lzl::utils {

template <typename T>
struct has_call_operator
{
private:
    template <typename U>
    static auto check(char) -> decltype(&U::operator(), std::true_type{});

    template <typename>
    static auto check(...) -> std::false_type;

public:
    static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
struct maybe_lambda
{
private:
    template <typename U>
    static bool check_id_name()
    {
        std::string name = typeid(U).name();
        // MSVC Clang
        if (name.find("lambda") != std::string::npos)
        {
            return true;
        }
        // GCC: It may not be accurate
        size_t firstPos = name.find("EUl");
        if (name.back() == '_' && firstPos != std::string::npos && firstPos == name.rfind("EUl"))
        {
            return true;
        }
        return false;
    }

public:
    static constexpr bool value() { return has_call_operator<T>::value && check_id_name<T>(); }
};

} // namespace lzl::utils

#endif // LZL_TYPE_MAYBE_LAMBDA_H
