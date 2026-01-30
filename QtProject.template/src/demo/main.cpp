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
#include "main_object.h"

#include <QApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>

// #include <lzl/settings>

#define APP_TITLE    APP_NAME " " APP_VERSION
#define APP_LOGO_URL ":/lzl/demo/logo"

#define logDebug   qDebug() << "[DEBUG][Main]"
#define logWarning qWarning() << "[WARNING][Main]"

int main(int argc, char* argv[])
{
    // 设置 Application 基本信息
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setOrganizationName(ORG_NAME);

    // 初始化当前工作目录
    QDir::setCurrent(QFileInfo(argv[0]).dir().absolutePath());

    // 初始化配置文件路径
    // lzl::Settings::InitIniDirectory(QDir::currentPath());

    // 创建应用
    QApplication app(argc, argv);

    // 设置默认标题和图标
    app.setApplicationDisplayName(QStringLiteral(APP_TITLE));
    app.setWindowIcon(QIcon(QStringLiteral(APP_LOGO_URL)));

    // 加载 Qt 翻译文件
    {
        const auto dir = QLibraryInfo::path(QLibraryInfo::TranslationsPath);
        auto translator = new QTranslator(&app);
        if (translator->load(QLocale::system(), "qtbase", "_", dir))
        {
            QCoreApplication::installTranslator(translator);
        }
        else
        {
            delete translator;
            logDebug << "Failed to load Qt translation file from" << dir;
        }
    }

    // 设置应用字体
    {
        QFont font(PROJ_NAMESPACE::demo::g_loadAppFont(QStringLiteral(":/lzl/demo/font/MapleMonoNormal-NF-CN-Regular")));
        font.setWeight(QFont::Medium);
        QApplication::setFont(font);
    }

    MainObject obj;
    obj.start();

    return app.exec();
}

/* ========================================================================== */
