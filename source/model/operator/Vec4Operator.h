#ifndef SHADERGRAPH_VEC4OPERATOR_H
#define SHADERGRAPH_VEC4OPERATOR_H

#include "model/Node.h"
#include "model/Data.h"

#define REGISTER_VECTOR4_OPERATORS(_register_) \
    _register_->registerModel<ShaderGraph::AddVector4Node>("Operator"); \
    _register_->registerModel<ShaderGraph::SubtractVector4Node>("Operator"); \
    _register_->registerModel<ShaderGraph::MultiplyVector4Node>("Operator"); \
    _register_->registerModel<ShaderGraph::DivideVector4Node>("Operator"); \


namespace ShaderGraph
{
    class AddVector4Node : public Node
    {
    public:
        AddVector4Node() : Node("AddVector4")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("A", this),
                    std::make_shared<Vector4>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Result", this)
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

    class SubtractVector4Node : public Node
    {
    public:
        SubtractVector4Node() : Node("SubtractVector4")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("A", this),
                    std::make_shared<Vector4>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Result", this)
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

    class MultiplyVector4Node : public Node
    {
    public:
        MultiplyVector4Node() : Node("MultiplyVector4")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("A", this),
                    std::make_shared<Vector4>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Result", this)
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

    class DivideVector4Node : public Node
    {
    public:
        DivideVector4Node() : Node("DivideVector4")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("A", this),
                    std::make_shared<Vector4>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Result", this)
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
}

#endif //SHADERGRAPH_VEC4OPERATOR_H
