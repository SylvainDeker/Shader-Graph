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
                    std::make_shared<Float>("A", this),
                    std::make_shared<Float>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("Result", this)
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

    class SubtractFloatNode : public Node
    {
    public:
        SubtractFloatNode() : Node("SubtractFloat")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("A", this),
                    std::make_shared<Float>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("Result", this)
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

    class MultiplyFloatNode : public Node
    {
    public:
        MultiplyFloatNode() : Node("MultiplyFloat")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("A", this),
                    std::make_shared<Float>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("Result", this)
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

    class DivideFloatNode : public Node
    {
    public:
        DivideFloatNode() : Node("DivideFloat")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("A", this),
                    std::make_shared<Float>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("Result", this)
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

#endif //SHADERGRAPH_FLOATOPERATOR_H
