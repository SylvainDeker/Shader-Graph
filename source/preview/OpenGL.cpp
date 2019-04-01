#include "OpenGL.h"

namespace ShaderGraph
{
    void glClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    bool glDumpError(const char * function, const char * file, int line)
    {
        bool isGlErrorBufferEmpty = true;
        while (GLenum error = glGetError())
        {
            isGlErrorBufferEmpty = false; // there is at least one error

            LOG_ERROR("OpenGL error : {0}. \n\tfile : {1} at the line : {2} \n\t common : {3}",
                      glErrorToString(error), file, line, function);
        }
        return isGlErrorBufferEmpty;
    }
}