#ifndef SHADERGRAPH_COMMONOPERATOR_H
#define SHADERGRAPH_COMMONOPERATOR_H

#include <nodes/DataModelRegistry>

#include "model/Node.h"

#include "pin/PinDecl.h"


#define COMMON_OPERATOR_TYPES std::vector<EPinType> {FLOAT, VEC2, VEC3, VEC4}

namespace ShaderGraph
{
    class AddNode : public Node
    {
    public:
        AddNode() : Node("+")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "ReturnValue", this)
            };
        }

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "{0} = {1} + {2};",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class SubtractNode : public Node
    {
    public:
        SubtractNode() : Node("-")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "X", this),
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "Y", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "Result", this)
            };
        }

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "{0} = {1} - {2};",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class MultiplyNode : public Node
    {
    public:
        MultiplyNode() : Node("*")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "Result", this)
            };
        }

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "{0} = {1} * {2};",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class DivideNode : public Node
    {
    public:
        DivideNode() : Node("/")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "Result", this)
            };
        }

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "{0} = {1} / {2};",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };
}

#endif //SHADERGRAPH_COMMONOPERATOR_H
