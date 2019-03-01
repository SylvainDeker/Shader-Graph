#include "Scene.h"

#include <QKeyEvent>

namespace ShaderGraph
{
    Scene::Scene(unsigned int width, unsigned int height) :
        m_width(width),
        m_height(height)
    {
        /* ============================================================ */
        /* Step 0 : OpenGL setup */
        /* ============================================================ */
        GL_ASSERT(glEnable(GL_BLEND));
        GL_ASSERT(glEnable(GL_DEPTH_TEST));

        GL_ASSERT(glViewport(0, 0, m_width, m_height));
        GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        /* ============================================================ */
        /* Step 1 : Setup camera */
        /* ============================================================ */
        m_camera = new TrackballCamera();
        m_camera->setViewport(glm::vec4(0.f, 0.f, width, height));

        m_projection = glm::perspective(m_camera->zoom(), (float)width / (float)height,  0.1f, 100.0f);

        /* ============================================================ */
        /* Step 2 : Load textures */
        /* ============================================================ */

        /* ============================================================ */
        /* Step 3 : Build materials */
        /* ============================================================ */

        /* ============================================================ */
        /* Step 4 : Build lights */
        /* ============================================================ */

        /* ============================================================ */
        /* Step 5 : Build static mesh */
        /* ============================================================ */

        /* ============================================================ */
        /* Step 6 : Compile shaders */
        /* ============================================================ */

}

    Scene::~Scene()
    {

    }

    void Scene::resize(unsigned int width, unsigned int height)
    {
        m_width  = width;
        m_height = height;
        GL_ASSERT(glViewport(0, 0, m_width, m_height));
    }

    void Scene::draw()
    {
        /* ============================================================ */
        /* Step 0 : OpenGL stuffs */
        /* ============================================================ */
        GL_ASSERT(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT));

        /* ============================================================ */
        /* Step 1 : Prepare each shader for the rendering */
        /* ============================================================ */

        /* ============================================================ */
        /* Step 2 : Rendering */
        /* ============================================================ */

    }

    void Scene::mouseClick(int button, float xpos, float ypos)
    {
        (void) button;
        m_mouseX = xpos;
        m_mouseY = ypos;
    }

    void Scene::mouseMove(float xpos, float ypos)
    {
        m_mouseX = xpos;
        m_mouseY = ypos;
    }
}