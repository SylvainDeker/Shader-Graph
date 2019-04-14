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
    /// Constructor.
    explicit GLWidget(QWidget * parent = nullptr);

    /// Destructor.
    ~GLWidget() override = default;

    /// OpenGL management : Call when to init OpenGL.
    void initializeGL() override;

    /// OpenGL management : Call every tick to do the rendering.
    void paintGL() override;

    /// OpenGL management : Call when the window's dim changed.
    void resizeGL(int width, int height) override;

    /// Mouse event : Press
    void mousePressEvent(QMouseEvent * event) override;

    /// Mouse event : Move
    void mouseMoveEvent(QMouseEvent * event) override;

    /// Event call when the button "compile" is pressed. Will update the preview.
    inline void onShaderCompiled(const std::string& generatedCode)
    {
        m_scene->onShaderCompiled(generatedCode);
        update();
    }

private:
    unsigned int m_lastTime;

    ShaderGraph::Scene * m_scene;
};

#endif // SHADERGRAPH_GLWIDGET_H
