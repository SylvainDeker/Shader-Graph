#ifndef SHADERGRAPH_VEC3OPERATOR_H
#define SHADERGRAPH_VEC3OPERATOR_H

#include "model/Node.h"
#include "model/Data.h"

#define REGISTER_VECTOR3_OPERATORS(_register_) \
    _register_->registerModel<ShaderGraph::AddVector3Node>("Operator"); \
    _register_->registerModel<ShaderGraph::SubtractVector3Node>("Operator"); \
    _register_->registerModel<ShaderGraph::MultiplyVector3Node>("Operator"); \
    _register_->registerModel<ShaderGraph::DivideVector3Node>("Operator"); \


namespace ShaderGraph
{
    class AddVector3Node : public Node
    {
    public:
        AddVector3Node() : Node("AddVector3")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("A", this),
                    std::make_shared<Vector3>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("Result", this)
            };
        }
    };

    class SubtractVector3Node : public Node
    {
    public:
        SubtractVector3Node() : Node("SubtractVector3")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("A", this),
                    std::make_shared<Vector3>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("Result", this)
            };
        }
    };

    class MultiplyVector3Node : public Node
    {
    public:
        MultiplyVector3Node() : Node("MultiplyVector3")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("A", this),
                    std::make_shared<Vector3>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("Result", this)
            };
        }
    };

    class DivideVector3Node : public Node
    {
    public:
        DivideVector3Node() : Node("DivideVector3")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("A", this),
                    std::make_shared<Vector3>("B", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("Result", this)
            };
        }
    };
}

#endif //SHADERGRAPH_VEC3OPERATOR_H
