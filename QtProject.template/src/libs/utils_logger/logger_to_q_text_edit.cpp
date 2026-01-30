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

#include "logger_to_q_text_edit.h"

#include <QScrollBar>
#include <QTimer>

#define LOG_VERBOSE_COLOR Qt::darkGreen
#define LOG_DEBUG_COLOR   Qt::blue
#define LOG_INFO_COLOR    Qt::black
#define LOG_WARN_COLOR    QColor(255, 140, 0) // 橙色
#define LOG_ERROR_COLOR   Qt::red

namespace PROJ_NAMESPACE::utils {

LoggerToQTextEdit::LoggerToQTextEdit(QTextEdit* editor) : LoggerObserver()
{
    setEditor(editor);
}

LoggerToQTextEdit::~LoggerToQTextEdit()
{
    if (m_editor != nullptr)
    {
        m_editor->disconnect(m_connection);
    }
}

void LoggerToQTextEdit::setEditor(QTextEdit* editor)
{
    if (m_editor != nullptr)
    {
        m_editor->disconnect(m_connection);
    }

    m_editor = editor;
    if (m_editor != nullptr)
    {
        m_connection = QObject::connect(m_editor, &QObject::destroyed, m_editor, [this]() { m_editor = nullptr; });
    }
}

/* ========================================================================== */

bool LoggerToQTextEdit::isValid() const
{
    return m_editor != nullptr;
}

void LoggerToQTextEdit::setLevel(Logger::Level level)
{
    Logger::assertLevel(level);
    if (isValid())
    {
        m_level = level;
    }
}

void LoggerToQTextEdit::output(const QString& msg)
{
    if (isValid())
    {
        // If the scrollbar is at the bottom, then go to the bottom, otherwise don't move
        auto atBottom = m_editor->verticalScrollBar()->value() == m_editor->verticalScrollBar()->maximum();
        auto cursor = m_editor->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.setCharFormat(getLevelFormat(m_editor->font().pointSize(), m_level));
        cursor.insertText(msg);
        if (atBottom)
        {
            m_editor->verticalScrollBar()->setValue(m_editor->verticalScrollBar()->maximum());
        }
    }
}

/* ========================================================================== */

const QTextCharFormat LoggerToQTextEdit::getLevelFormat(qreal pointSize, Logger::Level level)
{
    Logger::assertLevel(level);
    QTextCharFormat f;
    f.setFontPointSize(pointSize);
    if (level == Logger::LOG_VERBOSE)
    {
        f.setForeground(LOG_VERBOSE_COLOR);
    }
    else if (level == Logger::LOG_DEBUG)
    {
        f.setForeground(LOG_DEBUG_COLOR);
    }
    else if (level == Logger::LOG_INFO)
    {
        f.setForeground(LOG_INFO_COLOR);
    }
    else if (level == Logger::LOG_WARN)
    {
        f.setForeground(LOG_WARN_COLOR);
    }
    else if (level == Logger::LOG_ERROR)
    {
        f.setForeground(LOG_ERROR_COLOR);
        f.setFontWeight(QFont::Bold);
        f.setFontPointSize(pointSize * 1.25);
    }
    else
    {
    }
    return f;
}

} // namespace PROJ_NAMESPACE::utils
