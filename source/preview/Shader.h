#ifndef SHADERGRAPH_SHADER_H
#define SHADERGRAPH_SHADER_H

#include <string>

#include <core/Core.h>

#include "OpenGL.h"

namespace ShaderGraph
{
    class Shader
    {
    public:
        Shader(const std::string& filename);
        ~Shader();

        /// Bind this Shader (aka program).
        void bind() const;

        /// Unbind this Shader (aka program).
        void unbind() const;

        /// Set a uniform of the type : int.
        void setInt(const std::string &name, const int v);

        /// Set a uniform of the type : float.
        void setFloat(const std::string &name, const float v);

        /// Set a uniform of the type : vec3.
        void setVec3(const std::string &name, const glm::vec3 v);

        /// Set a uniform of the type : vec4.
        void setVec4(const std::string &name, const glm::vec4 v);

        /// Set a uniform of the type : mat4.
        void setMat4(const std::string &name, const glm::mat4 mat);

        /// Get the source code (glsl source code).
        const std::string& filename() const { return m_filename; }

        /// Get the id given by openGL.
        const int& id() const { return m_id; }

        /// Get the location of a uniform with its name.
        int getUniformLocation(const std::string& name);

        /// Get the location of a uniform with its name.
        int getUniformLocation(const std::string&& name);

    private:
        /// The location of the file.
        std::string m_filename;

        /// The id given by openGL.
        int m_id;

        struct ShaderProgramSource
        {
            std::string vertex;
            std::string fragment;
        };

        /// Read a glsl file and extract the vertex code and the fragment code.
        ShaderProgramSource parseShaderFile(const std::string& filename);

        /// Compile a glsl code depending on its type.
        int compileShader(unsigned int type, const std::string& source);

        /// Create a shader from the vertex code and the fragment code.
        int createShader(const std::string& vertexShader, const std::string& fragmentShader);
    };
}

#endif //SHADERGRAPH_SHADER_H
