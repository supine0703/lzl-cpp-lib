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

#ifndef _SRC__LIBS__UTILS_LOGGER_TO_Q_TEXT_EDIT_H
#define _SRC__LIBS__UTILS_LOGGER_TO_Q_TEXT_EDIT_H

#include "logger.h"

#include <QTextCharFormat>
#include <QTextEdit>

namespace PROJ_NAMESPACE::utils {

/**
 * @brief LoggerObserver implementation for QTextEdit
 */
class UTILS_LOGGER_EXPORT LoggerToQTextEdit final : public LoggerObserver
{
public:
    explicit LoggerToQTextEdit(QTextEdit* editor);
    ~LoggerToQTextEdit();

    void setEditor(QTextEdit* editor = nullptr);

    // LoggerObserver interface
public:
    virtual bool isValid() const override;
    virtual void setLevel(Logger::Level level) override;
    virtual void output(const QString& msg) override;

private:
    static const QTextCharFormat getLevelFormat(qreal pointSize, Logger::Level level);

private:
    QTextEdit* m_editor = nullptr;
    QMetaObject::Connection m_connection;
    Logger::Level m_level = Logger::LOG_LEVEL_MAX;
};

} // namespace PROJ_NAMESPACE::utils

#endif // _SRC__LIBS__UTILS_LOGGER_TO_Q_TEXT_EDIT_H
