#ifndef SHADERGRAPH_SCENE_H
#define SHADERGRAPH_SCENE_H

#include <core/Core.h>

#include "OpenGL.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"

#include "../model/Compilation.h"

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

        void onShaderCompiled(const std::string& uniforms,
                              const std::string& generatedCode,
                              const std::list<TextureData> textureData);

    protected:
        unsigned int m_width;  /// Width of the viewport
        unsigned int m_height; /// Heigth of the viewport

    private:
        /// Build Tangents and Bi-tangents
        void computeTangents();

    private:
        /* ==================================================================================== */
        /* Mouse management */
        /* ==================================================================================== */

        int   m_button = 0;
        float m_mouseX = 0;
        float m_mouseY = 0;

        /* ==================================================================================== */
        /* Managers */
        /* ==================================================================================== */

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

        glm::vec4   m_lightColor;
        glm::vec3   m_lightDir;

        /* ==================================================================================== */
        /* World stuffs */
        /* ==================================================================================== */

        std::vector<std::shared_ptr<Texture>> m_texture;

        /// Mesh : Vertices
        std::vector<glm::vec3> m_vertices;

        /// Mesh : Normals
        std::vector<glm::vec3> m_normals;

        /// Mesh : texture coordinates
        std::vector<glm::vec3> m_texCoords;

        /// Mesh : tangents
        std::vector<glm::vec3> m_tangents;

        /// Mesh : bi-tangents
        std::vector<glm::vec3> m_biTangents;

        /// Mesh : indices
        std::vector<unsigned int>  m_indices;

        /// Vertex Array Buffer Id
        unsigned int m_vao;

        /// Vertex Buffer Object Id
        unsigned int m_vbo;

        /// Normal buffer Id
        unsigned int m_nbo;

        /// Face buffer Id
        unsigned int m_ibo;

        /// Texture Coords buffer Id
        unsigned int m_ubo;

        /// Tangent buffer Id
        unsigned int m_tbo;

        /// Bi-tangent buffer Id
        unsigned int m_bbo;
    };
}

#endif // SHADERGRAPH_SCENE_H
