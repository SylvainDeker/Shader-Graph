#ifndef SHADERGRAPH_VEC2OPERATOR_H
#define SHADERGRAPH_VEC2OPERATOR_H

#include "model/Node.h"
#include "pin/Pin.h"

#define REGISTER_VECTOR2_OPERATORS(_register_) \
    _register_->registerModel<ShaderGraph::AddVector2Node>("Operator"); \
    _register_->registerModel<ShaderGraph::SubtractVector2Node>("Operator"); \
    _register_->registerModel<ShaderGraph::MultiplyVector2Node>("Operator"); \
    _register_->registerModel<ShaderGraph::DivideVector2Node>("Operator"); \


namespace ShaderGraph
{
    class AddVector2Node : public Node
    {
    public:
        AddVector2Node() : Node("AddVector2")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("A", this),
                    std::make_shared<Vector2>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("Result", this)
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

    class SubtractVector2Node : public Node
    {
    public:
        SubtractVector2Node() : Node("SubtractVector2")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("A", this),
                    std::make_shared<Vector2>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("Result", this)
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

    class MultiplyVector2Node : public Node
    {
    public:
        MultiplyVector2Node() : Node("MultiplyVector2")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("A", this),
                    std::make_shared<Vector2>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("Result", this)
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

    class DivideVector2Node : public Node
    {
    public:
        DivideVector2Node() : Node("DivideVector2")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("A", this),
                    std::make_shared<Vector2>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("Result", this)
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

#endif //SHADERGRAPH_Vector2OPERATOR_H
