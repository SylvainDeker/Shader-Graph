#include "Scene.h"

#include <QKeyEvent>

#include "Shader.h"

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
        m_camera = new TrackballCamera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f));
        m_camera->setViewport(glm::vec4(0.f, 0.f, width, height));
        
        m_view = m_camera->viewMatrix();
        m_projection = glm::perspective(m_camera->zoom(), float(m_width) / m_height, 0.1f, 100.0f);

        /* ============================================================ */
        /* Step 2 : Load textures */
        /* ============================================================ */

        /* ============================================================ */
        /* Step 3 : Build materials */
        /* ============================================================ */

        /* ============================================================ */
        /* Step 4 : Build lights */
        /* ============================================================ */
        m_lightcolor = glm::vec4(1.0, 1.0, 1.0, 1.0);
        m_lightdir = glm::normalize(glm::vec3(-0.5, -0.5, -0.5));
        /* ============================================================ */
        /* Step 5 : Build static mesh */
        /* ============================================================ */

        // Initialise geometric data
        m_vertices = {
                0.5f,  0.5f, 0.0f,  // Top Right
                0.5f, -0.5f, 0.0f,  // Bottom Right
                -0.5f, -0.5f, 0.0f,  // Bottom Left
                -0.5f,  0.5f, 0.0f   // Top Left
        };

        m_normals = {
                0.577350269189626f, 0.577350269189626f, 0.577350269189626f,
                0.577350269189626f, -0.577350269189626f, 0.577350269189626f,
                -0.577350269189626f, -0.577350269189626f, 0.577350269189626f,
                -0.577350269189626f, 0.577350269189626f, 0.577350269189626f
        };

        m_indices = {
                // Note that we start from 0!
                0, 1, 3,   // First Triangle
                1, 2, 3    // Second Triangle
        };

        // Initialize the geometry
        // 1. Generate geometry buffers
        glGenBuffers(1, &m_vbo) ;
        glGenBuffers(1, &m_nbo) ;
        glGenBuffers(1, &m_ibo) ;
        glGenVertexArrays(1, &m_vao) ;

        // 2. Bind Vertex Array Object
        glBindVertexArray(m_vao);

        // 3. Copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof (float), m_vertices.data(), GL_STATIC_DRAW);

        // 4. Then set our vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // 5. Copy our normals array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
        glBufferData(GL_ARRAY_BUFFER, m_normals.size()*sizeof (float), m_normals.data(), GL_STATIC_DRAW);

        // 6. Copy our vertices array in a buffer for OpenGL to use
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

        // 7. Copy our index array in a element buffer for OpenGL to use
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof (float), m_indices.data(), GL_STATIC_DRAW);

        //6. Unbind the VAO
        glBindVertexArray(0);

        /* ============================================================ */
        /* Step 6 : Compile shaders */
        /* ============================================================ */
        m_shader = new Shader("../data/shaders/RedShader.glsl");
    }

    Scene::~Scene()
    {
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_nbo);
        glDeleteBuffers(1, &m_ibo);
        glDeleteVertexArrays(1, &m_vao) ;

        delete m_shader;
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
        
        m_model = glm::mat4(1.0f);
        m_view = m_camera->viewMatrix();
        /* ============================================================ */
        /* Step 1 : Prepare each shader for the rendering */
        /* ============================================================ */
        m_shader->bind();
        
        m_shader->setMat4("model", m_model);
        m_shader->setMat4("view", m_view);
        m_shader->setMat4("projection", m_projection);

        m_shader->setVec4("dirlight.color", m_lightcolor);
        m_shader->setVec3("dirlight.direction", m_lightdir);

        /* ============================================================ */
        /* Step 2 : Rendering */
        /* ============================================================ */
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

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
}
