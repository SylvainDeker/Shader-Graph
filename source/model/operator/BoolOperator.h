#ifndef SHADERGRAPH_BOOLOPERATOR_H
#define SHADERGRAPH_BOOLOPERATOR_H

#include "model/Node.h"
#include "model/Data.h"

#define REGISTER_BOOL_OPERATORS(_register_) \
    _register_->registerModel<ShaderGraph::AndOperatorNode>("LogicalOperator"); \
    _register_->registerModel<ShaderGraph::OrOperatorNode>("LogicalOperator"); \

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
    };
}

#endif //SHADERGRAPH_BOOLOPERATOR_H
