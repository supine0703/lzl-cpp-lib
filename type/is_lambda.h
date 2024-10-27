/**
 * License: MIT
 * Copyright (c) 2024 Li Zonglin (李宗霖) github: <https://github.com/supine0703>
 * Repositories: lzl-cpp-lib <https://github.com/supine0703/lzl-cpp-lib>
 */

#ifndef LZL_TYPE_IS_LAMBDA_H
#define LZL_TYPE_IS_LAMBDA_H

namespace lzl::utils {

// template <typename T>
// struct is_lambda
//     : std::integral_constant<bool, std::is_class_v<T> && !std::is_same_v<T, std::decay_t<T>>>
// {
// };


// #if __cpp_concepts // C++20 or later
// template <typename T>
// concept IsLambda = requires(T t) {
//     { &T::operator() };
// };
// #endif // __cpp_concepts

} // namespace lzl::utils

#endif // LZL_TYPE_IS_LAMBDA_H
