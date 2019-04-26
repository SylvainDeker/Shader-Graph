#ifndef SHADERGRAPH_BOOLOPERATOR_H
#define SHADERGRAPH_BOOLOPERATOR_H

#include "model/Node.h"
#include "pin/Pin.h"

#define LOGICAL_OPERATOR_TYPES std::vector<EPinType> {BOOLEAN, FLOAT, VEC2, VEC3, VEC4}

namespace ShaderGraph
{
    class AndOperatorNode : public Node
    {
    public:
        AndOperatorNode() : Node("And")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Boolean>("A", this),
                    std::make_shared<Boolean>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Boolean>("Result", this)
            };
        }

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "{0} = {1} && {2};",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class OrOperatorNode : public Node
    {
    public:
        OrOperatorNode() : Node("Or")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Boolean>("A", this),
                    std::make_shared<Boolean>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Boolean>("Result", this)
            };
        }

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "{0} = {1} || {2};",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };


    class EqualNode : public Node
    {
    public:
        EqualNode() : Node("==")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(LOGICAL_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(LOGICAL_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Boolean>("Result", this)
            };
        }

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "{0} = {1} == {2};",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class NotEqualNode : public Node
    {
    public:
        NotEqualNode() : Node("!=")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(LOGICAL_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(LOGICAL_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Boolean>("Result", this)
            };
        }

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "{0} = {1} != {2};",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class GreaterNode : public Node
    {
    public:
        GreaterNode() : Node(">")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(LOGICAL_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(LOGICAL_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Boolean>("Result", this)
            };
        }

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "{0} = {1} > {2};",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class GreaterEqualNode : public Node
    {
    public:
        GreaterEqualNode() : Node(">=")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(LOGICAL_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(LOGICAL_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Boolean>("Result", this)
            };
        }

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "{0} = {1} >= {2};",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class LowerNode : public Node
    {
    public:
        LowerNode() : Node("<")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(LOGICAL_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(LOGICAL_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Boolean>("Result", this)
            };
        }

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "{0} = {1} < {2};",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };

    class LowerEqualNode : public Node
    {
    public:
        LowerEqualNode() : Node("<=")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(LOGICAL_OPERATOR_TYPES, 0, "A", this),
                    std::make_shared<Template>(LOGICAL_OPERATOR_TYPES, 0, "B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Boolean>("Result", this)
            };
        }

        GLSLData nodeToGLSL() override
        {
            GLSLData buffer;
            GLSL_CODE(buffer.generatedCode,
                      "{0} = {1} <= {2};",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };
}

#endif //SHADERGRAPH_BOOLOPERATOR_H
