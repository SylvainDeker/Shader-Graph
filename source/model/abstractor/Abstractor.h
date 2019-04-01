#ifndef SHADERGRAPH_ABSTRACTOR_H
#define SHADERGRAPH_ABSTRACTOR_H

#include "../Node.h"

#include "../../pin/PinDecl.h"

#define REGISTER_ABSTRACTOR_OPERATORS(_register_) \
_register_->registerModel<ShaderGraph::Vec4ToTemplate>("Abstractor"); \
_register_->registerModel<ShaderGraph::Vec2ToTemplate>("Abstractor"); \
_register_->registerModel<ShaderGraph::FxVecN>("Abstractor");\
_register_->registerModel<ShaderGraph::GxOnlyVec2>("Abstractor");\

namespace ShaderGraph
{
    class Vec4ToTemplate : public Node
    {
    public:
        Vec4ToTemplate() : Node("Vec4ToTemplate")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(VEC4, 0, "Result", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Vec4", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer, "Hello");
            return buffer;
        }
    };

    class Vec2ToTemplate : public Node
    {
    public:
        Vec2ToTemplate() : Node("Vec2ToTemplate")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(VEC4, 0, "Result", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("Vec2", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer, "Hello");
            return buffer;
        }
    };

    class FxVecN : public Node
    {
    public:
        FxVecN() : Node("FxVecN")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(std::vector<EPinType> {FLOAT, VEC2, VEC3, VEC4},
                                               0,
                                               "Result",
                                               this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(std::vector<EPinType> {FLOAT, VEC2, VEC3, VEC4},
                                               0,
                                               "Input",
                                               this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer, "Hello");
            return buffer;
        }
    };

    class GxOnlyVec2 : public Node
    {
    public:
        GxOnlyVec2() : Node("GxOnlyVec2")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(std::vector<EPinType> {VEC2}, 0, "Result", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(std::vector<EPinType> {VEC2}, 0, "Input", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer, "Hello");
            return buffer;
        }
    };
}

#endif //SHADERGRAPH_ABSTRACTOR_H
