#ifndef SHADERGRAPH_VECTORPIN_H
#define SHADERGRAPH_VECTORPIN_H

#include <core/Core.h>

#include "Pin.h"

namespace ShaderGraph
{
    class Vector2 : public GenType<glm::vec2>
    {
    public:
        /// Default constructor.
        explicit Vector2(QString name = "Vector2D", QtNodes::NodeDataModel * owner = nullptr) :
                GenType<glm::vec2>(glm::vec2(0.0f), name, owner, EPinType::VEC2)
        {

        };

        /// Constructor.
        explicit Vector2(glm::vec2 value, QString name = "Vector2D", QtNodes::NodeDataModel * owner = nullptr) :
                GenType<glm::vec2>(value, name, owner, EPinType::VEC2)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Vector2", name()};
        }

        /// @return : Get the GLSL type (in string) which represents this pin.
        std::string typeToGLSL() override { return "vec2"; }

        // TODO : comment me :)
        std::string defaultValueToGLSL() override { return "vec2(0.0f)"; }
    };

    class Vector3 : public GenType<glm::vec3>
    {
    public:
        /// Default constructor.
        explicit Vector3(QString name = "Vector3D", QtNodes::NodeDataModel * owner = nullptr) :
                GenType<glm::vec3>(glm::vec3(0.0f), name, owner, EPinType::VEC3)
        {

        };

        /// Constructor.
        explicit Vector3(glm::vec3 value, QString name = "Vector3D", QtNodes::NodeDataModel * owner = nullptr) :
                GenType<glm::vec3>(value, name, owner, EPinType::VEC3)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Vector3", name()};
        }

        /// @return : Get the GLSL type (in string) which represents this pin.
        std::string typeToGLSL() override { return "vec3"; }

        // TODO : comment me :)
        std::string defaultValueToGLSL() override { return "vec3(0.0f)"; }
    };

    class Vector4 : public GenType<glm::vec4>
    {
    public:
        /// Default constructor.
        explicit Vector4(QString name = "Vector4D", QtNodes::NodeDataModel * owner = nullptr) :
                GenType<glm::vec4>(glm::vec4(0.0f), name, owner, EPinType::VEC4)
        {

        };

        /// Constructor.
        explicit Vector4(glm::vec4 value, QString name = "Vector4D", QtNodes::NodeDataModel * owner = nullptr) :
                GenType<glm::vec4>(value, name, owner, EPinType::VEC4)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Vector4", name()};
        }

        /// @return : Get the GLSL type (in string) which represents this pin.
        std::string typeToGLSL() override { return "vec4"; }

        // TODO : comment me :)
        std::string defaultValueToGLSL() override { return "vec4(0.0f)"; }
    };
}

#endif //SHADERGRAPH_VECTORPIN_H
