#ifndef SHADERGRAPH_FROMTEMPLATE_H
#define SHADERGRAPH_FROMTEMPLATE_H

#include <nodes/TypeConverter>
#include <nodes/DataModelRegistry>

#include "../Node.h"
#include "../../pin/PinDecl.h"

namespace ShaderGraph
{
    void registerFromTemplateConverters(std::shared_ptr<QtNodes::DataModelRegistry> registry);

    class BoolFromTemplate : public Node
    {
    public:
        BoolFromTemplate() : Node("BoolFromTemplate")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(BOOLEAN, 0, "Result", this)
            };

            outputs() = std::vector<PIN> {
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

    class ScalarFromTemplate : public Node
    {
    public:
        ScalarFromTemplate() : Node("ScalarFromTemplate")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(FLOAT, 0, "Result", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("Scalar", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer, "/* TODO : in = out */");
            return buffer;
        }
    };

    class Vec2FromTemplate : public Node
    {
    public:
        Vec2FromTemplate() : Node("Vec2FromTemplate")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(VEC2, 0, "Result", this)
            };

            outputs() = std::vector<PIN> {
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

    class Vec3FromTemplate : public Node
    {
    public:
        Vec3FromTemplate() : Node("Vec3FromTemplate")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(VEC3, 0, "Result", this)
            };

            outputs() = std::vector<PIN> {
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

    class Vec4FromTemplate : public Node
    {
    public:
        Vec4FromTemplate() : Node("Vec4FromTemplate")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(VEC4, 0, "Result", this)
            };

            outputs() = std::vector<PIN> {
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

#endif //SHADERGRAPH_FROMTEMPLATE_H
