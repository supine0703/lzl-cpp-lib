/**
 * License: MIT
 * Copyright (c) 2024 Li Zonglin (李宗霖) github: <https://github.com/supine0703>
 * Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>
 */

#ifndef LZL_TYPE_MAYBE_LAMBDA_H
#define LZL_TYPE_MAYBE_LAMBDA_H

#include <string>
#include <typeinfo>

#if __cpp_concepts

namespace lzl::utils {

template <typename T>
concept HasCallOperator = requires() {
    { &T::operator() };
};

template <typename T>
struct has_call_operator
{
    static constexpr bool value = HasCallOperator<T>;
};

template <typename T>
struct maybe_lambda
{
private:
    static constexpr bool is_lambda()
    {
        std::string name = typeid(T).name();
        // MSVC and Clang
        if (name.find("lambda") != std::string::npos)
        {
            return true;
        }
        // GCC: may not be accurate
        size_t firstPos = name.find("EUl");
        if (name.ends_with("_") && firstPos != std::string::npos && firstPos == name.rfind("EUl"))
        {
            return true;
        }
        return false;
    }

public:
    static constexpr bool value()
    {
        return has_call_operator<T>::value && maybe_lambda::is_lambda();
    }
};

} // namespace lzl::utils

#endif // __cpp_concepts

#endif // LZL_TYPE_MAYBE_LAMBDA_H
