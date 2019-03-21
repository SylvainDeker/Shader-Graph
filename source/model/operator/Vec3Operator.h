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

#endif //SHADERGRAPH_VEC3OPERATOR_H
