#ifndef SHADERGRAPH_SCENE_H
#define SHADERGRAPH_SCENE_H

#include <core/Core.h>

#include "OpenGL.h"
#include "Camera.h"

namespace ShaderGraph
{
    class Scene
    {
    public:
        explicit Scene(unsigned int width, unsigned int height);
        virtual ~Scene();

        virtual void resize(unsigned int width, unsigned int height);
        virtual void draw();

        virtual void mouseClick(int button, float xpos, float ypos);
        virtual void mouseMove(float xpos, float ypos);

    protected:
        unsigned int m_width;  /// Width of the viewport
        unsigned int m_height; /// Heigth of the viewport

    private:
        /* ==================================================================================== */
        /* Mouse management */
        /* ==================================================================================== */
        float  m_mouseX = 0;
        float  m_mouseY = 0;

        /* ==================================================================================== */
        /* Managers */
        /* ==================================================================================== */
        // TODO : add managers

        /* ==================================================================================== */
        /* World stuffs */
        /* ==================================================================================== */
        Camera *    m_camera;
        glm::mat4   m_projection;
    };
};

#endif // SHADERGRAPH_SCENE_H