#ifndef SHADERGRAPH_TOTEMPLATE_H
#define SHADERGRAPH_TOTEMPLATE_H

#include <nodes/DataModelRegistry>

#include "../Node.h"
#include "../../pin/PinDecl.h"

namespace ShaderGraph
{
    void registerToTemplateConverters(std::shared_ptr<QtNodes::DataModelRegistry> registry);

    class BoolToTemplate : public Node
    {
    public:
        BoolToTemplate() : Node("BoolToTemplate")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(BOOLEAN, 0, "Result", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Boolean>("Boolean", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer, "/* TODO : in = out */");
            return buffer;
        }
    };

    class ScalarToTemplate : public Node
    {
    public:
        ScalarToTemplate() : Node("ScalarToTemplate")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(FLOAT, 0, "Result", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("Scalar", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer, "/* Do nothing : ScalarToTemplate */");
            return buffer;
        }
    };

    class Vec2ToTemplate : public Node
    {
    public:
        Vec2ToTemplate() : Node("Vec2ToTemplate")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(VEC2, 0, "Result", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Vector2>("Vec2", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer, "/* TODO : in = out */");
            return buffer;
        }
    };

    class Vec3ToTemplate : public Node
    {
    public:
        Vec3ToTemplate() : Node("Vec3ToTemplate")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(VEC3, 0, "Result", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("Vec3", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer, "/* TODO : in = out */");
            return buffer;
        }
    };

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
            GLSL_CODE(buffer, "/* TODO : in = out */");
            return buffer;
        }
    };
}

#endif //SHADERGRAPH_TOTEMPLATE_H
