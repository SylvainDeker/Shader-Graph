#include "Shader.h"

#include <fstream> // Read a file with the C API instead of the C++ API is more efficient
#include <sstream>

namespace ShaderGraph
{
    Shader::Shader(const std::string& filename) :
            m_filename(filename)
    {
        const ShaderProgramSource shaderProgramSource = parseShaderFile(filename);
        m_id = createShader(shaderProgramSource.vertex, shaderProgramSource.fragment);
        unbind(); // By default, a shader is unbind after creation.
    }

    Shader::~Shader()
    {
        GL_ASSERT(glDeleteProgram(m_id));
    }

    void Shader::bind() const
    {
        GL_ASSERT(glUseProgram(m_id));
    }

    void Shader::unbind() const
    {
        GL_ASSERT(glUseProgram(GL_NULL_ID));
    }

    Shader::ShaderProgramSource Shader::parseShaderFile(const std::string& filename)
    {
        std::string line;
        std::ifstream stream(filename);
        std::stringstream ss[2];

        if (!stream.is_open())
        {
             LOG_CRITICAL("Shader::parseShaderFile : file not found : {0}", filename);
        }


        enum EShaderType { None = -1, Vertex = 0, Frag = 1 };
        EShaderType type = EShaderType::None;

        while (std::getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = EShaderType::Vertex;

                else if (line.find("fragment") != std::string::npos)
                    type = EShaderType::Frag;

            }
            else if (type != EShaderType::None)
                ss[(int)type] << line << "\n";
        }
        return {ss[0].str(), ss[1].str() } ;
    }

    int Shader::compileShader(unsigned int type, const std::string& source)
    {
        unsigned int shaderId = glCreateShader(type);
        const char * cSource = source.c_str();

        GL_ASSERT(glShaderSource(shaderId, 1, &cSource, nullptr));
        GL_ASSERT(glCompileShader(shaderId));

        int result = 0;
        GL_ASSERT(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result));

        if (result == GL_FALSE) /* check if an error occurred */
        {
            int len = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &len);
            char * errmsg = (char *) alloca(len * sizeof(char));

            glGetShaderInfoLog(shaderId, len, &len, errmsg);

            LOG_ERROR("Shader::CompileShader : {0}, compilation failed with {1}",
                      (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), errmsg);

            return -1;
        }
        return shaderId;
    }

    int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        int program = glCreateProgram();
        int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        if (vs < 0 || fs < 0) return -1; // The compilation has failed..

        GL_ASSERT(glAttachShader(program, vs));
        GL_ASSERT(glAttachShader(program, fs));

        GL_ASSERT(glLinkProgram(program));
        GL_ASSERT(glValidateProgram(program));

        GL_ASSERT(glDeleteShader(vs));
        GL_ASSERT(glDeleteShader(fs));

        return program;
    }

    int Shader::getUniformLocation(const std::string& name)
    {
        const int kUndefinedLocation = -1;
        const int kLocation = glGetUniformLocation(m_id, name.c_str());

        if (kLocation == kUndefinedLocation)
        {
             LOG_ERROR("Shader::getUniformLocation, uniform : {0} not found.", name);
        }
        
        return kLocation;
    }

    int Shader::getUniformLocation(const std::string&& name)
    {
        const int kUndefinedLocation = -1;
        const int kLocation = glGetUniformLocation(m_id, name.c_str());

        if (kLocation == kUndefinedLocation)
        {
             LOG_ERROR("Shader::getUniformLocation, uniform : {0} not found.", name);
        }

        return kLocation;
    }

    void Shader::setInt(const std::string& name, int v)
    {
        const int kLocation = getUniformLocation(name);
        GL_ASSERT(glUniform1i(kLocation, v));
    }

    void Shader::setVec3(const std::string& name, const glm::vec3 v)
    {
        const int kLocation = getUniformLocation(name);
        GL_ASSERT(glUniform3f(kLocation, v.x, v.y, v.z));
    }

    void Shader::setVec4(const std::string& name, const glm::vec4 v)
    {
        const int kLocation = getUniformLocation(name);
        GL_ASSERT(glUniform4f(kLocation, v.x, v.y, v.z, v.a));
    }

    void Shader::setFloat(const std::string& name, float v)
    {
        const int kLocation = getUniformLocation(name);
        GL_ASSERT(glUniform1f(kLocation, v));
    }

    void Shader::setMat4(const std::string& name, const glm::mat4 mat)
    {
        const int kLocation = getUniformLocation(name);
        GL_ASSERT(glUniformMatrix4fv(kLocation, 1, GL_FALSE, &mat[0][0]));
    }
}