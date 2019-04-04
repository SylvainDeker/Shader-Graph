#ifndef SHADERGRAPH_INTERFACE_H
#define SHADERGRAPH_INTERFACE_H

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include <core/Core.h>

namespace ShaderGraph
{
    enum EPinType
    {
        TEMPLATE,
        BOOLEAN,
        FLOAT,
        VEC2,
        VEC3,
        VEC4
    };

    inline EPinType pinTypeFromString(std::string& type)
    {
        if (type == "Boolean")      return EPinType::BOOLEAN;
        else if (type == "Float")   return EPinType::FLOAT;
        else if (type == "Vector2") return EPinType::VEC2;
        else if (type == "Vector3") return EPinType::VEC3;
        else if (type == "Vector4") return EPinType::VEC4;
        else                        return EPinType::TEMPLATE;
    }

    inline std::string pinTypeToString(EPinType type)
    {
        switch (type)
        {
            case EPinType::BOOLEAN :    return "Boolean";
            case EPinType::FLOAT :      return "Float";
            case EPinType::VEC2 :       return "Vec2";
            case EPinType::VEC3 :       return "Vec3";
            case EPinType::VEC4 :       return "Vec4";
            default:                    return "Template";
        }
    }

    class IPin
    {
    public:
        /// Default destructor.
        virtual ~IPin() = default;

        /* ============================== Connection ============================== */

        /// @return : True if this pin is connected to an other pin.
        virtual bool isConnected() const = 0;

        /// Getter : The connected pin.
        /// @return : nullptr if this pin isn't connected.
        virtual std::shared_ptr<QtNodes::NodeData> getConnectedPin() = 0;

        /// Connect the pin to an other pin.
        virtual void connect(std::shared_ptr<QtNodes::NodeData> inPin) = 0;

        /// Disconnect this pin if it was connected.
        virtual void disconnect() = 0;

        /* ============================== Pin Type ============================== */

        /// Getter : The type of this pin.
        virtual EPinType getType() const = 0;

        /// Setter : The type of this pin.
        virtual void setType(EPinType type) = 0;

        /* ============================== Container / Owner ============================== */

        /// Getter : The node which contains this pin.
        virtual QtNodes::NodeDataModel * getNode() = 0;

        /// Setter : The node which contains this pin.
        virtual void setNode(QtNodes::NodeDataModel * owner) = 0;

        /* ============================== Code Generation ============================== */

        /// @return : Get the GLSL type (in string) which represents this pin.
        virtual std::string typeToGLSL() = 0;

        // @return : Get the GLSL default value (in string) in case of this pin is disconnected during code generation.
        virtual std::string defaultValueToGLSL() = 0;

        /// @return : Get name of this pin to std::string.
        virtual std::string nameToGLSL() = 0;
    };
}

#endif //SHADERGRAPH_INTERFACE_H
