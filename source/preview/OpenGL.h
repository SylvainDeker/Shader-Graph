#ifndef SHADERGRAPH_OPENGL_H
#define SHADERGRAPH_OPENGL_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include <string>

#include <core/Core.h>

#define GL_NULL_ID 0

namespace ShaderGraph
{
    /// Cast a GLError to a string
    inline std::string glErrorToString(GLenum Error)
    {
        switch (Error) {
            case GL_NO_ERROR:
                return " No error";
            case GL_INVALID_ENUM:
                return " Invalid enum : An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
            case GL_INVALID_VALUE:
                return " Invalid value : A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
            case GL_INVALID_OPERATION:
                return " Invalid operation : The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                return " Invalid framebuffer operation : The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
            case GL_OUT_OF_MEMORY:
                return " Out of memory : There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
            default:
                return " Unknown OpenGL error.";
        }
    }

    /// Clear the errors in the GLErrorBuffer
    void glClearError();

    /// Dump each error in the GLErrorBuffer
    /// @return : true if no error
    bool glDumpError(const char * function, const char * file, int line);

    #define GL_ASSERT(_function_) \
        if (true) \
        { \
            ShaderGraph::glClearError(); \
            _function_; \
            ShaderGraph::glDumpError(#_function_, __FILE__, __LINE__); \
        } \
    // end GL_CALL
}

#endif //SHADERGRAPH_OPENGL_H
