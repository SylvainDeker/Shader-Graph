#include "GLWidget.h"

#include <QDateTime>
#include <QApplication>

#define LAST_TIME_START_VALUE 0

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent), 
    QOpenGLFunctions_4_1_Core(),
    m_lastTime(LAST_TIME_START_VALUE)
{

}

void GLWidget::initializeGL()
{
    if (!initializeOpenGLFunctions())
    {
        LOG_CRITICAL("GLWidget::initializeGL : Cannot initialize OpenGL functions");
    }
    m_scene = new ShaderGraph::Scene(WIDTH, HEIGHT);

    LOG_INFO("OpenGL initialization : [OK]");
}

void GLWidget::paintGL()
{
    const unsigned int startTime = QDateTime::currentMSecsSinceEpoch();

    m_scene->draw();
    GL_ASSERT(glFinish());

    const unsigned int endTime   = QDateTime::currentMSecsSinceEpoch();
    m_lastTime = endTime - startTime;
}

void GLWidget::resizeGL(int width, int height)
{
    m_scene->resize(width, height);
}

void GLWidget::mousePressEvent(QMouseEvent * event)
{
    int buttonType; // buttons are 0 = left, 1 = right to 2 = middle
    Qt::MouseButton button = event->button();

    if (button & Qt::LeftButton)
    {
        if ((event->modifiers() & Qt::ControlModifier)) buttonType = 2;
        else buttonType = 0;
    }
    else if (button & Qt::RightButton) buttonType = 1;
    else if (button & Qt::MiddleButton) buttonType = 2;
    else buttonType = 3;

    m_scene->mouseClick(buttonType, event->x(), event->y());
    update();
}

void GLWidget::mouseMoveEvent(QMouseEvent * event)
{
    m_scene->mouseMove(event->x(), event->y());
    update();
}
