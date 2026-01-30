#include "window_controller.h"

namespace PROJ_NAMESPACE::demo {

WindowController::WindowController(QObject* parent)
    : QObject(parent)
    , m_currentModeWindow(nullptr)
{
}

WindowController::~WindowController()
{
    setCurrentModeWindow(nullptr);
}

/* ========================================================================== */

void WindowController::start()
{
    setCurrentModeWindow(new QWidget());
}

/* ========================================================================== */

void WindowController::setCurrentModeWindow(QWidget* window)
{
    if (m_currentModeWindow != nullptr)
    {
        m_currentModeWindow->hide();
        m_currentModeWindow->deleteLater();
    }
    if (m_currentModeWindow = window; m_currentModeWindow != nullptr)
    {
        m_currentModeWindow->show();
    }
}

} // namespace PROJ_NAMESPACE::demo
