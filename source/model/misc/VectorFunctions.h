#ifndef SHADERGRAPH_VECTORFUNCTIONS_H
#define SHADERGRAPH_VECTORFUNCTIONS_H

#include "../Node.h"
#include "pin/Pin.h"

namespace ShaderGraph
{
    class MakeVec2Node : public Node
    {
    public:
        MakeVec2Node() : Node("MakeVec2")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("Vector2", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("X", this),
                    std::make_shared<Float>("Y", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "{0} = vec2({1}, {2});"
                      "",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class MakeVec3Node : public Node
    {
    public:
        MakeVec3Node() : Node("MakeVec3")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("Vector3", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("X", this),
                    std::make_shared<Float>("Y", this),
                    std::make_shared<Float>("Z", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "{0} = vec3({1}, {2}, {3});"
                      "",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]),
                      autoName(inputs()[2]));
            return buffer;
        }
    };

    class MakeVec4Node : public Node
    {
    public:
        MakeVec4Node() : Node("MakeVec4")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Vector4", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("X", this),
                    std::make_shared<Float>("Y", this),
                    std::make_shared<Float>("Z", this),
                    std::make_shared<Float>("A", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "{0} = vec4({1}, {2}, {3}, {4});"
                      "",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]),
                      autoName(inputs()[2]),
                      autoName(inputs()[3]));
            return buffer;
        }
    };

    class BreakVec2Node : public Node
    {
    public:
        BreakVec2Node() : Node("BreakVec2")
        {
            inputs() = std::vector<PIN> {
                std::make_shared<Vector2>("Vector2", this)
            };

            outputs() = std::vector<PIN> {
                std::make_shared<Float>("X", this),
                std::make_shared<Float>("Y", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "{1} = {0}.x;"
                      "{2} = {0}.y;"
                      "",

                      autoName(inputs()[0]),

                      autoName(outputs()[0]),
                      autoName(outputs()[1]));
            return buffer;
        }
    };

    class BreakVec3Node : public Node
    {
    public:
        BreakVec3Node() : Node("BreakVec3")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("Vector3", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("X", this),
                    std::make_shared<Float>("Y", this),
                    std::make_shared<Float>("Z", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "{1} = {0}.x;"
                      "{2} = {0}.y;"
                      "{3} = {0}.z;"
                      "",

                      autoName(inputs()[0]),

                      autoName(outputs()[0]),
                      autoName(outputs()[1]),
                      autoName(outputs()[2]));
            return buffer;
        }
    };

    class BreakVec4Node : public Node
    {
    public:
        BreakVec4Node() : Node("BreakVec4")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Vector4", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("X", this),
                    std::make_shared<Float>("Y", this),
                    std::make_shared<Float>("Z", this),
                    std::make_shared<Float>("A", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "{1} = {0}.x;"
                      "{2} = {0}.y;"
                      "{3} = {0}.z;"
                      "{4} = {0}.a;"
                      "",

                      autoName(inputs()[0]),

                      autoName(outputs()[0]),
                      autoName(outputs()[1]),
                      autoName(outputs()[2]),
                      autoName(outputs()[3]));
            return buffer;
        }
    };
}

#endif //SHADERGRAPH_VECTORFUNCTIONS_H
