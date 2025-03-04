/*******************************************************************************
**
** License: MIT
** Copyright (c) 2024-2025 李宗霖 (Li Zonglin)
** Email: supine0703@outlook.com
** GitHub: https://github.com/supine0703
** Repository: https://github.com/supine0703/lzl-cpp-lib
**
*******************************************************************************/

#if __cpp_if_constexpr // c++17
    #include "cxx17/typename.h"
#elif __cplusplus >= 201103L || _MSVC_LANG >= 201103L
    #include "cxx11/typename.h"
#endif // __cplusplus || _MSVC_LANG
