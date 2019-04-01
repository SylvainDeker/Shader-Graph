#ifndef SHADERGRAPH_BOOLOPERATOR_H
#define SHADERGRAPH_BOOLOPERATOR_H

#include "model/Node.h"
#include "pin/Pin.h"

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

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "{0} = {1} && {2}",
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

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "{0} = {1} || {2}",
                      autoName(outputs()[0]),
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };
}

#endif //SHADERGRAPH_BOOLOPERATOR_H
