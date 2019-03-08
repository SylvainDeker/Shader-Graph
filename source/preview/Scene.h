#ifndef SHADERGRAPH_SCENE_H
#define SHADERGRAPH_SCENE_H

#include <core/Core.h>

#include "OpenGL.h"
#include "Camera.h"
#include "Shader.h"

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
        float m_button = 0;
        float m_mouseX = 0;
        float m_mouseY = 0;

        /* ==================================================================================== */
        /* Managers */
        /* ==================================================================================== */
        // TODO : add managers

        Shader * m_shader;

        /* ==================================================================================== */
        /* World stuffs */
        /* ==================================================================================== */
        Camera *    m_camera;
        glm::mat4   m_projection;
        glm::mat4   m_view;
        glm::mat4   m_model;
        glm::vec4   m_lightcolor;
        glm::vec3   m_lightdir;

        /* ==================================================================================== */
        /* World stuffs */
        /* ==================================================================================== */

        // A simple geometry
        std::vector<float> m_vertices;
        std::vector<float> m_normals;
        std::vector<unsigned int>  m_indices;

        // OpenGL object for geometry

        // Vertex Array Buffer
        unsigned int m_vao;
        // Vertex Buffer Object
        unsigned int m_vbo;
        // Normal buffer
        unsigned int m_nbo;
        // Face buffer
        unsigned int m_ibo;
    };
};

#endif // SHADERGRAPH_SCENE_H
