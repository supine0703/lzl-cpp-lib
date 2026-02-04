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
/*******************************************************************************
**
** License: MIT
** Copyright (c) 2016 - present, Gabi Melman and spdlog contributors.
** Repository: https://github.com/gabime/spdlog
**
*******************************************************************************/

// #include "_logging/init.h"

#include "global.h"
#include "main_object.h"

#include <QApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>

// #include <lzl/settings>
// #include <spdlog/spdlog.h>


#define APP_TITLE    APP_NAME " " APP_VERSION
#define APP_LOGO_URL QRC_PREFIX "/logo"

#define LOG_FLAG "[Main]"

// namespace {
// void logMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
// {
//     std::string text(msg.toLocal8Bit().constData());
//     switch (type)
//     {
//     case QtDebugMsg:
//         spdlog::debug(text);
//         break;
//     case QtInfoMsg:
//         spdlog::info(text);
//         break;
//     case QtWarningMsg:
//         spdlog::warn(text);
//         break;
//     case QtCriticalMsg:
//         spdlog::error(text);
//         break;
//     case QtFatalMsg:
//         spdlog::critical(text);
//         // abort();  // Qt 默认行为已包含 abort 调用
//         break;
//     }
// }
// } // namespace

int main(int argc, char* argv[])
{
    // 设置高DPI缩放策略
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    #if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    #endif
#endif

    // 设置 Application 基本信息
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setOrganizationName(ORG_NAME);

    // 初始化当前工作目录
    QDir::setCurrent(QFileInfo(argv[0]).dir().absolutePath());

    // 创建日志目录
// #if LOGGING_FILE_ENABLED
//     QDir().mkpath(LOGGING_FILE_DIR);
// #endif

    // 初始化配置文件路径
    // lzl::Settings::InitIniDirectory(QDir::currentPath());

    // 创建应用
    QApplication app(argc, argv);

    // 初始化日志系统
// #if LOGGING_ENABLED
//     try
//     {
//         PROJ_NAMESPACE::demo::initLogging();
//     }
//     catch (const spdlog::spdlog_ex& ex)
//     {
//         qCritical() << LOG_FLAG << "Log initialization failed:" << ex.what();
//         return EXIT_FAILURE;
//     }

//     // 安装日志处理器
//     ::qInstallMessageHandler(::logMessageHandler);
// #endif // LOGGING_ENABLED

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
        else if (translator->load(QLocale::system(), "qt", "_", dir))
        {
            QCoreApplication::installTranslator(translator);
        }
        else
        {
            delete translator;
            qWarning() << LOG_FLAG << "Failed to load Qt translation file from" << dir;
        }
    }

    // 设置应用字体
    {
        using namespace PROJ_NAMESPACE::demo;
        QFont font(g_loadAppFont(QStringLiteral(QRC_PREFIX "/font/MapleMonoNormal-NF-CN-Regular")));
        font.setWeight(QFont::Medium);
        QApplication::setFont(font);
    }

    MainObject obj;
    obj.start();

    return app.exec();
}

/* ========================================================================== */
