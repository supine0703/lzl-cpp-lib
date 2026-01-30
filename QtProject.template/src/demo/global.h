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

#ifndef _SRC__DEMO__GLOBAL_H
#define _SRC__DEMO__GLOBAL_H

#include "disable.h"

#include <QStringList>

namespace PROJ_NAMESPACE::demo {

class __Global final
{
    DISABLE_CONSTRUCT(__Global)

    // 获取应用程序绝对路径
public:
    static QString appAbsolutePath(const QString& relativePath);

    // 加载字体
public:
    static QString loadAppFont(const QString& fontPath);
    static QStringList loadAppFonts(const QStringList& fontPaths);

    // 加载 Iconfont
public:
    static QString loadIconfont();

    enum IconfontUnicode : quint16 {
        SWITCH_LEFT = 0xe6f1,
        SWITCH_RIGHT = 0xe6f2,
        SWITCH_LOCK = 0xe6f3,
        SWITCH_UNLOCK = 0xe6f4,
        BUTTON_CLEAR = 0xe6f5,
        BUTTON_POWER = 0xe6f6,
    };
    // ...
};

#define g_appAbsolutePath    __Global::appAbsolutePath
#define g_loadAppFont        __Global::loadAppFont
#define g_loadAppFonts       __Global::loadAppFonts
#define g_loadIconfont       __Global::loadIconfont
#define g_iconfontUnicode(X) QChar(static_cast<quint16>(__Global::IconfontUnicode::X))

} // namespace PROJ_NAMESPACE::demo

#endif // _SRC__DEMO__GLOBAL_H
