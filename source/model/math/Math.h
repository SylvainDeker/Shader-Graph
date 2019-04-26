#ifndef SHADERGRAPH_MATH_H
#define SHADERGRAPH_MATH_H


#include <core/Core.h>

#include "../Node.h"

namespace ShaderGraph
{
    class StepNode : public Node
    {
        Q_OBJECT

    public:
        StepNode();

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "// Step \n"
                      "{0} = floor({1} / {2}) * {2};\n"
                      "\n",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };
}


#endif //SHADERGRAPH_MATH_H
