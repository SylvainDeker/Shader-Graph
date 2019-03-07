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
                    std::make_shared<Vector4>("A"),
                    std::make_shared<Vector4>("B")
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Result")
            };
        }
    };

    class SubtractVector4Node : public Node
    {
    public:
        SubtractVector4Node() : Node("SubtractVector4")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("A"),
                    std::make_shared<Vector4>("B")
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Result")
            };
        }
    };

    class MultiplyVector4Node : public Node
    {
    public:
        MultiplyVector4Node() : Node("MultiplyVector4")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("A"),
                    std::make_shared<Vector4>("B")
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Result")
            };
        }
    };

    class DivideVector4Node : public Node
    {
    public:
        DivideVector4Node() : Node("DivideVector4")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("A"),
                    std::make_shared<Vector4>("B")
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Result")
            };
        }
    };
}

#endif //SHADERGRAPH_VEC4OPERATOR_H
