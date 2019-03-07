#ifndef SHADERGRAPH_VEC2OPERATOR_H
#define SHADERGRAPH_VEC2OPERATOR_H

#include "model/Node.h"
#include "model/Data.h"

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
                    std::make_shared<Vector2>("A"),
                    std::make_shared<Vector2>("B")
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("Result")
            };
        }
    };

    class SubtractVector2Node : public Node
    {
    public:
        SubtractVector2Node() : Node("SubtractVector2")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("A"),
                    std::make_shared<Vector2>("B")
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("Result")
            };
        }
    };

    class MultiplyVector2Node : public Node
    {
    public:
        MultiplyVector2Node() : Node("MultiplyVector2")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("A"),
                    std::make_shared<Vector2>("B")
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("Result")
            };
        }
    };

    class DivideVector2Node : public Node
    {
    public:
        DivideVector2Node() : Node("DivideVector2")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("A"),
                    std::make_shared<Vector2>("B")
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("Result")
            };
        }
    };
}

#endif //SHADERGRAPH_Vector2OPERATOR_H
