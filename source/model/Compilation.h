#ifndef SHADERGRAPH_COMPILER_H
#define SHADERGRAPH_COMPILER_H

#include <string>
#include <list>

#include <core/Core.h>

#define GLSL_CODE(_code_, ...) \
do \
{ \
    fmt::memory_buffer membuf; \
    format_to(membuf, __VA_ARGS__); \
    _code_ = to_string(membuf); \
} while (false); \

namespace ShaderGraph
{
    struct TextureData
    {
        std::string name;
        std::string path;
    };

    struct GLSLData
    {
        std::string generatedCode;
        std::string uniforms;

        bool hasFailed = false;
        std::string errmsg;

        std::list<TextureData> texturePaths;

        inline GLSLData operator+(const GLSLData& glslData) const
        {
            GLSLData output;
            output.generatedCode = generatedCode + glslData.generatedCode;
            output.uniforms = uniforms + glslData.uniforms;
            output.hasFailed = hasFailed || glslData.hasFailed;
            output.errmsg = errmsg + glslData.errmsg;

            output.texturePaths = texturePaths;
            output.texturePaths.insert(output.texturePaths.end(),
                                       glslData.texturePaths.begin(),
                                       glslData.texturePaths.end());

            return output;
        }
    };
}

#endif //SHADERGRAPH_COMPILER_H
