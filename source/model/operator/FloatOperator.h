#ifndef SHADERGRAPH_FLOATOPERATOR_H
#define SHADERGRAPH_FLOATOPERATOR_H

#include "model/Node.h"
#include "model/Data.h"

#define REGISTER_FLOAT_OPERATORS(_register_) \
    _register_->registerModel<ShaderGraph::AddFloatNode>("Operator"); \
    _register_->registerModel<ShaderGraph::SubtractFloatNode>("Operator"); \
    _register_->registerModel<ShaderGraph::MultiplyFloatNode>("Operator"); \
    _register_->registerModel<ShaderGraph::DivideFloatNode>("Operator"); \


namespace ShaderGraph
{
    class AddFloatNode : public Node
    {
    public:
        AddFloatNode() : Node("AddFloat")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("A"),
                    std::make_shared<Float>("B")
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("Result")
            };
        }
    };

    class SubtractFloatNode : public Node
    {
    public:
        SubtractFloatNode() : Node("SubtractFloat")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("A"),
                    std::make_shared<Float>("B")
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("Result")
            };
        }
    };

    class MultiplyFloatNode : public Node
    {
    public:
        MultiplyFloatNode() : Node("MultiplyFloat")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("A"),
                    std::make_shared<Float>("B")
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("Result")
            };
        }
    };

    class DivideFloatNode : public Node
    {
    public:
        DivideFloatNode() : Node("DivideFloat")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("A"),
                    std::make_shared<Float>("B")
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("Result")
            };
        }
    };
}

#endif //SHADERGRAPH_FLOATOPERATOR_H
