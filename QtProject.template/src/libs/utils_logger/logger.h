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

#ifndef _SRC__LIBS__UTILS_LOGGER_H
#define _SRC__LIBS__UTILS_LOGGER_H

#include "disable.h"
#include "lib_logger_exports.h"

#include <QHash>
#include <QMetaType>
#include <QObject>
#include <QString>

namespace PROJ_NAMESPACE::utils {

class LoggerObserver;

class UTILS_LOGGER_EXPORT Logger final : QObject
{
    DISABLE_COPY_MOVE(Logger)
    Q_OBJECT

public:
    using LevelType = int;
    enum Level : LevelType {
        LOG_LEVEL_BEGIN = 0,
        LOG_VERBOSE = LOG_LEVEL_BEGIN,
        LOG_DEBUG,
        LOG_INFO,
        LOG_WARN,
        LOG_ERROR,
        LOG_LEVEL_MAX
    };
    struct Info
    {
        LevelType level;
        QString message;
    };

    static int qRegisterMetaType_Info() { return ::qRegisterMetaType<Info>("PROJ_NAMESPACE::utils::Logger::Info"); }

public:
    explicit Logger(QObject* parent = nullptr) : Logger(nullptr, parent) {}
    explicit Logger(LoggerObserver* observer, QObject* parent = nullptr) : QObject(parent), m_observer(observer) {}
    ~Logger();

    Level logLevel() const noexcept { return m_currLevel; }
    const QString& logLevelStr() const noexcept { return logLevelStr(m_currLevel); }

    void setLevel(LevelType level = LOG_INFO) noexcept { m_currLevel = castLevel(level); }
    void setLevel(const QString& level) { m_currLevel = logStrToLevel(level); }

    void setObserver(LoggerObserver* observer) noexcept { m_observer = observer; }
    void destroyObserver() noexcept;

    // Observer is Used to output log message
public:
    bool isValid() const;
    void output(const QString& msg);
    void output(LevelType level, const QString& msg);
    void output(const Info& info) { output(info.level, info.message); }

private:
    LoggerObserver* m_observer;
    Level m_currLevel = LOG_INFO;

public:
    static const QString& logLevelStr(LevelType level) noexcept { return s_levelToStr[castLevel(level)]; }

    static Level logStrToLevel(const QString& str)
    {
        auto it = s_strToLevel.find(str);
        Q_ASSERT(it != s_strToLevel.end());
        return it.value();
    }

public:
    static constexpr bool isValidLevel(LevelType level) noexcept
    {
        return LOG_LEVEL_BEGIN <= level && level < LOG_LEVEL_MAX;
    }
    static constexpr void assertLevel(LevelType level) noexcept { Q_ASSERT(isValidLevel(level)); }
    static constexpr Level castLevel(LevelType level) noexcept { return assertLevel(level), static_cast<Level>(level); }

private:
    static const QString s_levelToStr[LOG_LEVEL_MAX];
    static const QHash<QString, Level> s_strToLevel;
};

/* ========================================================================== */

/**
 * @brief LoggerObserver interface (will be destroyed by Logger)
 */
class UTILS_LOGGER_EXPORT LoggerObserver
{
public:
    virtual ~LoggerObserver() = default;
    virtual bool isValid() const { return false; }
    virtual void setLevel(Logger::Level level) = 0;
    virtual void output(const QString& msg) = 0;
};

} // namespace PROJ_NAMESPACE::utils

#endif // _SRC__LIBS__UTILS_LOGGER_H
