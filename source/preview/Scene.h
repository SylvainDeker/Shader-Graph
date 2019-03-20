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
        glm::mat4   m_modelView;
        glm::mat4   m_mvp;
        glm::mat4   m_worldNormal;
        glm::mat4   m_viewNormal;

        glm::vec4   m_Kd;
        glm::vec4   m_Ks;
        float       m_roughness;

        glm::vec4   m_lightcolor;
        glm::vec3   m_lightdir;

        /* ==================================================================================== */
        /* World stuffs */
        /* ==================================================================================== */

        // A simple geometry
        std::vector<glm::vec3> m_vertices;
        std::vector<glm::vec3> m_normals;
        std::vector<glm::vec3> m_texcoords;
        std::vector<glm::vec3> m_tangents;
        std::vector<glm::vec3> m_bitangents;
        std::vector<unsigned int>  m_indices;

        /// Build Tangents and Bitangents
        void computeTangents();

        // OpenGL object for geometry

        // Vertex Array Buffer
        unsigned int m_vao;
        // Vertex Buffer Object
        unsigned int m_vbo;
        // Normal buffer
        unsigned int m_nbo;
        // Face buffer
        unsigned int m_ibo;
        // Texture Coords buffer
        unsigned int m_ubo;
        // Tangent buffer
        unsigned int m_tbo;
        // Bitangent buffer
        unsigned int m_bbo;

    };
}

#endif // SHADERGRAPH_SCENE_H
