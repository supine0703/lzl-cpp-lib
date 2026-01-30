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

#include "logger.h"

#include <QStringLiteral>

namespace PROJ_NAMESPACE::utils {

Logger::~Logger()
{
    destroyObserver();
}

void Logger::destroyObserver() noexcept
{
    if (m_observer != nullptr)
    {
        delete m_observer;
        m_observer = nullptr;
    }
}

bool Logger::isValid() const
{
    return isValidLevel(m_currLevel) && (m_observer != nullptr && m_observer->isValid());
}

void Logger::output(const QString& msg)
{
    output(m_currLevel, msg);
}

void Logger::output(LevelType level, const QString& msg)
{
    if (m_observer != nullptr && m_observer->isValid())
    {
        m_observer->setLevel(castLevel(level));
        m_observer->output(msg);
    }
}

/* ========================================================================== */

const QString Logger::s_levelToStr[] = {
    QStringLiteral("VERBOSE"),
    QStringLiteral("DEBUG"),
    QStringLiteral("INFO"),
    QStringLiteral("WARN"),
    QStringLiteral("ERROR")
};

const QHash<QString, Logger::Level> Logger::s_strToLevel = {
    {s_levelToStr[0], LOG_VERBOSE},
    {s_levelToStr[1], LOG_DEBUG  },
    {s_levelToStr[2], LOG_INFO   },
    {s_levelToStr[3], LOG_WARN   },
    {s_levelToStr[4], LOG_ERROR  }
};

} // namespace PROJ_NAMESPACE::utils
