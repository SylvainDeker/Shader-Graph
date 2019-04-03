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
        AddNode() : Node("Add")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "Result", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "{0} = {1} + {2}",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class SubtractNode : public Node
    {
    public:
        SubtractNode() : Node("Subtract")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "Result", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "{0} = {1} - {2}",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class MultiplyNode : public Node
    {
    public:
        MultiplyNode() : Node("Multiply")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "Result", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "{0} = {1} * {2}",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class DivideNode : public Node
    {
    public:
        DivideNode() : Node("Divide")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(COMMON_OPERATOR_TYPES, 0, "Result", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "{0} = {1} / {2}",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };
}

#endif //SHADERGRAPH_COMMONOPERATOR_H
