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
** License: MIT
** Copyright (c) 2016 - present, Gabi Melman and spdlog contributors.
** Repository: https://github.com/gabime/spdlog
**
*******************************************************************************/

#ifndef _SRC__DEMO__LOGGING__INIT_H
#define _SRC__DEMO__LOGGING__INIT_H

#ifndef LOGGING_STDOUT_ENABLED
    #define LOGGING_STDOUT_ENABLED 0
#endif

#ifndef LOGGING_FILE_ENABLED
    #define LOGGING_FILE_ENABLED 0
#endif

#define LOGGING_ENABLED (LOGGING_STDOUT_ENABLED || LOGGING_FILE_ENABLED)

namespace PROJ_NAMESPACE::demo {
void initLogging();
} // namespace PROJ_NAMESPACE::demo

#endif // _SRC__DEMO__LOGGING__INIT_H
