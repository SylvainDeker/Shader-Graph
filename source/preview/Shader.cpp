#include "Shader.h"

#include <fstream> // Read a file with the C API instead of the C++ API is more efficient
#include <sstream>
#include <regex>

namespace ShaderGraph
{
    Shader::Shader(const std::string& vertexshaderpath, const std::string& fragmentshaderpath)
    {
        m_fragmentShaderPath = fragmentshaderpath;
        const ShaderProgramSource shaderProgramSource = parseShaderFile(vertexshaderpath, fragmentshaderpath);
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

    Shader::ShaderProgramSource Shader::parseShaderFile(const std::string& vertexshaderpath, const std::string& fragmentshaderpath)
    {
        std::stringstream ss[2];

        // Extract Vertex Shader
        ss[0] << "#version 330\n\n"; // Header
        ss[0] << readGLSLFile(vertexshaderpath, 0);

        // Extract Fragment Shader

        ss[1] << "#version 330\n\n"; // Header
        ss[1] << readGLSLFile(fragmentshaderpath, 0);

        return {ss[0].str(), ss[1].str() } ;
    }

    int Shader::compileShader(unsigned int type, const std::string& source)
    {
        int shaderId = glCreateShader(type);
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
        m_fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        if (vs < 0 || m_fs < 0) return -1; // The compilation has failed..

        GL_ASSERT(glAttachShader(program, vs));
        GL_ASSERT(glAttachShader(program, m_fs));

        GL_ASSERT(glLinkProgram(program));

        int valid;
        glGetProgramiv(program, GL_LINK_STATUS, &valid);
        if (!valid)
        {
            LOG_CRITICAL("Shader::createShader : program could not be linked");
        }

        GL_ASSERT(glValidateProgram(program));

        GL_ASSERT(glDeleteShader(vs));
        GL_ASSERT(glDeleteShader(m_fs));

        return program;
    }

    void Shader::refresh()
    {
        // Read new shader
        std::stringstream new_frag;
        new_frag << "#version 330\n\n"; // Header
        new_frag << readGLSLFile(m_fragmentShaderPath, 0);

        // Compile new shader
        int new_fs = compileShader(GL_FRAGMENT_SHADER, new_frag.str());

        if (new_fs == -1)
        {
            LOG_ERROR("Shader::refresh : could not compile shader");
        }
        else
        {
            // Detach and activate deletion flag of old shader
            GL_ASSERT(glDetachShader(m_id, m_fs));

            // Attach new shader
            GL_ASSERT(glAttachShader(m_id, new_fs));
            m_fs = new_fs;

            GL_ASSERT(glLinkProgram(m_id));

            int valid;
            glGetProgramiv(m_id, GL_LINK_STATUS, &valid);
            if (!valid)
            {
                LOG_CRITICAL("Shader::refresh : program could not be linked");
            }

            GL_ASSERT(glValidateProgram(m_id));

            // Set deletion flag of new shader
            GL_ASSERT(glDeleteShader(m_fs));

            LOG_INFO("Successfully refreshed shader program");
        }
    }

    std::string Shader::readGLSLFile(const std::string& filepath, int level)
    {
        if (level >= 32)
        {
            LOG_CRITICAL("Shader::readGLSLFile : include recursion went too deep");
        }

        std::ifstream f_stream(filepath);

        if (!f_stream.is_open())
        {
             LOG_CRITICAL("Shader::readGLSLFile : GLSL file not found : {0}", filepath);
        }


        std::stringstream ss;
        std::string line;

        static const std::regex reg("^[ ]*#[ ]*include[ ]+[\"<](.*)[\">].*");
        size_t found = filepath.find_last_of("/");
        std::string folder = filepath.substr(0, found + 1);

        while (std::getline(f_stream, line))
        {
            std::smatch match;
            if (std::regex_search(line, match, reg))
            {
                std::string includepath = folder + match[1].str();
                ss << readGLSLFile(includepath, 0);
            }
            else
                ss << line << "\n";
        }

        return ss.str();
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
