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

#include "global.h"

#include <QApplication>
#include <QDir>
#include <QFontDatabase>

using namespace PROJ_NAMESPACE::demo;

QString __Global::appAbsolutePath(const QString& relativePath)
{
    Q_ASSERT(QCoreApplication::instance() != nullptr);

    // 判断是否是绝对路径
    if (QDir::isAbsolutePath(relativePath))
    {
        return relativePath;
    }

    // 获取应用程序绝对路径
    return QDir::toNativeSeparators(QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(relativePath));
}

/* ========================================================================== */

QString __Global::loadAppFont(const QString& fontPath)
{
    Q_ASSERT(QCoreApplication::instance() != nullptr);

    auto fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId != -1)
    {
        return QFontDatabase::applicationFontFamilies(fontId).at(0);
    }
    return QApplication::font().family();
}

QStringList __Global::loadAppFonts(const QStringList& fontPaths)
{
    QStringList fontFamilies;
    for (auto& fontPath : std::as_const(fontPaths))
    {
        fontFamilies.append(loadAppFont(fontPath));
    }
    return fontFamilies;
}

/* ========================================================================== */

QString __Global::loadIconfont()
{
    return loadAppFont(QStringLiteral(":/lzl/demo/font/iconfont"));
}
