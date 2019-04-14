#include "Scene.h"

#include <fstream>
#include <string>
#include <cmath>
#include <QKeyEvent>

#include "Shader.h"
#include "glm/gtc/matrix_transform.hpp"

namespace ShaderGraph
{
    Scene::Scene(unsigned int width, unsigned int height) :
        m_width(width),
        m_height(height)
    {
        /* ============================================================ */
        /* Step -1 : Restore the "MaterialModel" */
        /* ============================================================ */
        // Copy the "MaterialModel" reference
        std::ifstream input("../data/shaders/source/MaterialModel.glsl");
        assert(input.is_open());
        std::string content((std::istreambuf_iterator<char>(input)),
                            (std::istreambuf_iterator<char>()    ));
        input.close();

        // Paste the "MaterialModel" reference
        std::ofstream output("../data/shaders/runtime/Material.glsl");
        assert(output.is_open());
        output << content;
        output.flush();
        output.close();

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
        m_camera = new TrackballCamera(glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f));
        m_camera->setViewport(glm::vec4(0.f, 0.f, width, height));

        m_view = m_camera->viewMatrix();
        m_projection = glm::perspective(m_camera->zoom(), float(m_width) / m_height, 0.1f, 100.0f);
        m_model = glm::mat4(1.0f);
        m_modelView = m_view * m_model;
        m_mvp = m_projection * m_modelView;
        m_worldNormal = glm::transpose(glm::inverse(m_model));
        m_viewNormal = glm::transpose(glm::inverse(m_modelView));

        /* ============================================================ */
        /* Step 2 : Load textures */
        /* ============================================================ */

        /* ============================================================ */
        /* Step 4 : Build lights */
        /* ============================================================ */

        m_lightColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
        m_lightDir = glm::normalize(glm::vec3(-0.5, -0.5, -0.5));

        /* ============================================================ */
        /* Step 5 : Build static mesh */
        /* ============================================================ */

        // Initialise geometric data
        int nbLatitudeLines = 32;
        int nbLongitudeLines = 32;
        int nbVertices = nbLatitudeLines * nbLongitudeLines + 2;
        float radius = 1.0f;

        /* VERTICES AND NORMALS */
        m_vertices  = std::vector<glm::vec3>(static_cast<unsigned int>(nbVertices));
        m_normals   = std::vector<glm::vec3>(static_cast<unsigned int>(nbVertices));
        m_texCoords = std::vector<glm::vec3>(static_cast<unsigned int>(nbVertices));

        //North
        m_vertices[0] = glm::vec3(0,radius,0);
        m_normals[0] = glm::vec3(0,1,0);
        float u = std::atan2(m_normals[0][0], m_normals[0][2]) / (2*glm::pi<float>()) + 0.5;
        float v = m_normals[0][1] * 0.5 + 0.5;
        m_texCoords[0] = glm::vec3(u, v, 0);

        //South
        m_vertices[nbVertices - 1] = glm::vec3(0,-radius,0);
        m_normals[nbVertices - 1] = glm::vec3(0,-1,0);
        u = std::atan2(m_normals[nbVertices - 1][0], m_normals[nbVertices - 1][2]) / (2*glm::pi<float>()) + 0.5;
        v = m_normals[nbVertices - 1][1] * 0.5 + 0.5;
        m_texCoords[nbVertices - 1] = glm::vec3(u, v, 0);

        float latitudeSpacing = 1.0f / (nbLatitudeLines + 1.0f);
        float longitudeSpacing = 1.0f / nbLongitudeLines;

        int index = 1;
        for(int latitude = 0; latitude < nbLatitudeLines; ++latitude)
        {
            for(int longitude = 0; longitude < nbLongitudeLines; ++longitude)
            {
                float phi = longitude * longitudeSpacing * 2.0f * glm::pi<float>();
                float theta = ((latitude + 1) * latitudeSpacing) * glm::pi<float>();

                float x = sin(theta)*sin(phi);
                float y = cos(theta);
                float z = sin(theta)*cos(phi);

                m_normals[index] = glm::vec3(x, y, z);
                m_vertices[index] = glm::vec3(x, y, z) * radius;

                u = std::atan2(m_normals[index][0], m_normals[index][2]) / (2*glm::pi<float>()) + 0.5;
                v = m_normals[index][1] * 0.5 + 0.5;
                m_texCoords[index++] = glm::vec3(u, v, 0);

            }
        }

        int nbTriangles = 2*nbLongitudeLines*nbLatitudeLines;
        m_indices = std::vector<unsigned int>(3 * static_cast<unsigned int>(nbTriangles));
        index = 0;

        /* TRIANGLES */
        // North and South
        for (unsigned int longitude = 0; longitude < static_cast<unsigned int>(nbLongitudeLines); ++longitude)
        {
            unsigned int tmp = (longitude + 1) % nbLongitudeLines + 1;
            m_indices[index++] = 0;
            m_indices[index++] = longitude + 1;
            m_indices[index++] = tmp;

            m_indices[index++] = static_cast<unsigned int>(nbVertices) - 1;
            m_indices[index++] = static_cast<unsigned int>(nbVertices) - longitude - 2;
            m_indices[index++] = static_cast<unsigned int>(nbVertices) - tmp - 1;
        }
        // Others
        for (unsigned int latitude = 0; latitude < static_cast<unsigned int>(nbLatitudeLines) - 1; ++latitude)
        {
            for (unsigned int longitude = 0; longitude < static_cast<unsigned int>(nbLongitudeLines) - 1; ++longitude)
            {
                unsigned int current = latitude*nbLongitudeLines + longitude + 1;
                m_indices[index++] = current;
                m_indices[index++] = current + nbLongitudeLines;
                m_indices[index++] = current + nbLongitudeLines + 1;

                m_indices[index++] = current;
                m_indices[index++] = current + nbLongitudeLines + 1;
                m_indices[index++] = current + 1;
            }

            unsigned int current = latitude*nbLongitudeLines + nbLongitudeLines;
            m_indices[index++] = current;
            m_indices[index++] = current + nbLongitudeLines;
            m_indices[index++] = current + 1;

            m_indices[index++] = current;
            m_indices[index++] = current + 1;
            m_indices[index++] = latitude*nbLongitudeLines + 1;
        }

        computeTangents();

        // 1. Generate geometry buffers
        glGenBuffers(1, &m_vbo) ;
        glGenBuffers(1, &m_nbo) ;
        glGenBuffers(1, &m_ibo) ;
        glGenBuffers(1, &m_ubo) ;
        glGenBuffers(1, &m_tbo) ;
        glGenBuffers(1, &m_bbo) ;
        glGenVertexArrays(1, &m_vao) ;

        // 2. Bind Vertex Array Object
        glBindVertexArray(m_vao);

        // 3. Copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof (glm::vec3), m_vertices.data(), GL_STATIC_DRAW);

        // 4. Then set our vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // 5. Copy our normals array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
        glBufferData(GL_ARRAY_BUFFER, m_normals.size()*sizeof (glm::vec3), m_normals.data(), GL_STATIC_DRAW);

        // 6. Copy our vertices array in a buffer for OpenGL to use
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

        // 7. Copy our texture coordinates array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, m_ubo);
        glBufferData(GL_ARRAY_BUFFER, m_texCoords.size()*sizeof (glm::vec3), m_texCoords.data(), GL_STATIC_DRAW);

        // 8. Copy our vertices array in a buffer for OpenGL to use
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);

        // 9. Copy our tangents array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, m_tbo);
        glBufferData(GL_ARRAY_BUFFER, m_tangents.size()*sizeof (glm::vec3), m_tangents.data(), GL_STATIC_DRAW);

        // 10. Copy our vertices array in a buffer for OpenGL to use
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(3);

        // 11. Copy our bitangents array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, m_bbo);
        glBufferData(GL_ARRAY_BUFFER, m_biTangents.size()*sizeof (glm::vec3), m_biTangents.data(), GL_STATIC_DRAW);

        // 12. Copy our vertices array in a buffer for OpenGL to use
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(4);

        // 13. Copy our index array in a element buffer for OpenGL to use
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof (float), m_indices.data(), GL_STATIC_DRAW);

        // 14. Unbind the VAO
        glBindVertexArray(0);

        /* ============================================================ */
        /* Step 6 : Compile shaders */
        /* ============================================================ */
        m_shader = new Shader("../data/shaders/runtime/Vertex.glsl",
                              "../data/shaders/runtime/Fragment.glsl");
    }

    Scene::~Scene()
    {
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_nbo);
        glDeleteBuffers(1, &m_ibo);
        glDeleteVertexArrays(1, &m_vao) ;

        delete m_shader;
    }

    void Scene::computeTangents()
    {
        for (size_t i=0; i < m_indices.size(); i += 3)
        {
            glm::vec3 & v0 = m_vertices[m_indices[i]];
            glm::vec3 & v1 = m_vertices[m_indices[i+1]];
            glm::vec3 & v2 = m_vertices[m_indices[i+2]];

            glm::vec3 & uv0 = m_texCoords[m_indices[i]];
            glm::vec3 & uv1 = m_texCoords[m_indices[i+1]];
            glm::vec3 & uv2 = m_texCoords[m_indices[i+2]];

            // Edges of the triangle : position delta
            glm::vec3 deltaPos1 = v1-v0;
            glm::vec3 deltaPos2 = v2-v0;

            // UV delta
            glm::vec3 deltaUV1 = uv1-uv0;
            glm::vec3 deltaUV2 = uv2-uv0;

            float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
            glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
            glm::vec3 biTangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

            m_tangents.push_back(tangent);
            m_tangents.push_back(tangent);
            m_tangents.push_back(tangent);

            m_biTangents.push_back(biTangent);
            m_biTangents.push_back(biTangent);
            m_biTangents.push_back(biTangent);
        }
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

        m_view = m_camera->viewMatrix();
        m_modelView = m_view * m_model;
        m_mvp = m_projection * m_modelView;
        m_viewNormal = glm::transpose(glm::inverse(m_modelView));

        /* ============================================================ */
        /* Step 1 : Prepare each shader for the rendering */
        /* ============================================================ */

        m_shader->bind();

        m_shader->setMat4("transform.model", m_model);
        m_shader->setMat4("transform.view", m_view);
        m_shader->setMat4("transform.proj", m_projection);
        m_shader->setMat4("transform.mvp", m_mvp);
        m_shader->setMat4("transform.modelView", m_modelView);
        m_shader->setMat4("transform.worldNormal", m_worldNormal);
        m_shader->setMat4("transform.viewNormal", m_viewNormal);

        m_shader->setVec4("material.kd", glm::vec4(0.f));
        m_shader->setVec4("material.ks", glm::vec4(0.f));
        m_shader->setFloat("material.roughness", 0.000f);

        m_shader->setInt("light.type", 0); // Directional Light
        m_shader->setVec4("light.color", m_lightColor);
        m_shader->setVec3("light.directional.direction", m_lightDir);

        /* ============================================================ */
        /* Step 2 : Rendering */
        /* ============================================================ */
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);

        m_shader->unbind();
        glBindVertexArray(0);

    }

    void Scene::mouseClick(int button, float xpos, float ypos)
    {
        m_mouseX = xpos;
        m_mouseY = ypos;
        m_button = button;
        m_camera->processMouseClick(button, xpos, ypos);
    }

    void Scene::mouseMove(float xpos, float ypos)
    {
        m_mouseX = xpos;
        m_mouseY = ypos;
        m_camera->processMouseMovement(m_button, xpos, ypos);
    }

    void Scene::onShaderCompiled(const std::string& generatedCode)
    {
        std::ofstream output("../data/shaders/runtime/Material.glsl");
        assert(output.is_open());

        // Copy the "MaterialModelHeader" reference
        std::ifstream header("../data/shaders/source/MaterialModelHeader.txt");
        assert(header.is_open());
        std::string headerContent((std::istreambuf_iterator<char>(header)),
                                  (std::istreambuf_iterator<char>()    ));
        header.close();

        output << headerContent;

        std::string kdFunction = "vec3 getKd(Material material, vec2 texCoord) { \n" +
                                 generatedCode                                       +
                                 "\nreturn Diffuse; \n"                                +
                                 "} \n"                                              ;

        std::string ksFunction = "vec3 getKs(Material material, vec2 texCoord) { \n" +
                                 generatedCode                                       +
                                 "\nreturn Specular; \n"                               +
                                 "} \n"                                              ;

        std::string roughnessFunction = "vec2 getRoughness(Material material, vec2 texCoord) { \n" +
                                 generatedCode                                                     +
                                 "\nreturn vec2(Roughness); \n"                                    +
                                 "} \n"                                                            ;

        output << "\n\n" << kdFunction << "\n" << ksFunction << "\n" << roughnessFunction << "\n";

        // Copy the "MaterialModelFooter" reference
        std::ifstream footer("../data/shaders/source/MaterialModelFooter.txt");
        assert(footer.is_open());
        std::string footerContent((std::istreambuf_iterator<char>(footer)),
                                  (std::istreambuf_iterator<char>()    ));
        footer.close();

        output << footerContent;

        // Close and flush the header
        output.flush();
        output.close();

        delete m_shader;
        m_shader = new Shader("../data/shaders/runtime/Vertex.glsl",
                              "../data/shaders/runtime/Fragment.glsl");
        draw();
    }
}
