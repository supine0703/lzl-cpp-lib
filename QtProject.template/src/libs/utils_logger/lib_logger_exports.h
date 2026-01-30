/*******************************************************************************
**
** License: MIT
** Copyright (c) 2024-2025 李宗霖 (Li Zonglin)
** Email: supine0703@outlook.com
** GitHub: https://github.com/supine0703
** Repository: https://github.com/supine0703/lzl-cpp-lib
**
*******************************************************************************/
/*******************************************************************************
**
** License: GPLv3 and LGPLv3
** Copyright (c) Qt Project (www.qt.io)
**
*******************************************************************************/

#ifndef _SRC__LIBS__UTILS_LOGGER_EXPORTS_H
#define _SRC__LIBS__UTILS_LOGGER_EXPORTS_H

#include <QtGlobal>

#if defined(UTILS_LOGGER_SHARED) || !defined(UTILS_LOGGER_STATIC)
    #if defined(UTILS_LOGGER_LIBRARY)
        #define UTILS_LOGGER_EXPORT Q_DECL_EXPORT
    #else
        #define UTILS_LOGGER_EXPORT Q_DECL_IMPORT
    #endif
#else
    #define UTILS_LOGGER_EXPORT
#endif

#endif // _SRC__LIBS__UTILS_LOGGER_EXPORTS_H
