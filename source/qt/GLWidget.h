#ifndef SHADERGRAPH_GLWIDGET_H
#define SHADERGRAPH_GLWIDGET_H

#define WIDTH  1024
#define HEIGHT 1024

#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_1_Core>

#include <core/Core.h>

#include "../preview/Scene.h"
#include "../preview/OpenGL.h"

class GLWidget :
    public QOpenGLWidget, 
    public QOpenGLFunctions_4_1_Core 
{

public:
    explicit GLWidget(QWidget * parent = 0);

    ~GLWidget() = default;

    // OpenGL management
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    // Mouse events
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;

private:
    unsigned int m_lastTime;

    ShaderGraph::Scene * m_scene;
};

#endif // SHADERGRAPH_GLWIDGET_H
