#ifndef _SRC__DEMO__OBJECT__WINDOW_CONTROLLER_H
#define _SRC__DEMO__OBJECT__WINDOW_CONTROLLER_H

#include <QWidget>

namespace PROJ_NAMESPACE::demo {

class WindowController : public QObject
{
    Q_OBJECT

    // 构造与析构
public:
    explicit WindowController(QObject* parent = nullptr);
    ~WindowController();

    // 公有方法
public:
    void start();

    // 私有方法
private:
    void setCurrentModeWindow(QWidget* window);

    // 私有成员变量
private:
    QWidget* m_currentModeWindow;
};

} // namespace PROJ_NAMESPACE::demo

#endif // _SRC__DEMO__OBJECT__WINDOW_CONTROLLER_H
