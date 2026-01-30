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

#ifndef _SRC__DEMO__MAIN_OBJECT_H
#define _SRC__DEMO__MAIN_OBJECT_H

#include "object/window_controller.h"

class MainObject : public QObject
{
    Q_OBJECT

public:
    explicit MainObject(QObject* parent = nullptr) : QObject(parent) {}
    ~MainObject() = default;

public:
    void start() { m_windowController.start(); }

private:
    PROJ_NAMESPACE::demo::WindowController m_windowController;
};

#endif // _SRC__DEMO__MAIN_OBJECT_H
