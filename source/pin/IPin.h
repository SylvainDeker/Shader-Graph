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

        /// Connect the pin to an other pin.
        virtual void connect(std::shared_ptr<QtNodes::NodeData> inPin) = 0;

        /// Disconnect this pin if it was connected.
        virtual void disconnect() = 0;

        /// Getter : The connected pin.
        /// @return : nullptr if this pin isn't connected.
        virtual std::shared_ptr<QtNodes::NodeData> getConnectedPin() = 0;

        virtual EPinType getType() = 0;

        virtual void setType(EPinType type) = 0;

        /* ============================== Container / Owner ============================== */

        /// Getter : The node which contains this pin.
        virtual QtNodes::NodeDataModel * getNode() = 0;

        /// Setter : The node which contains this pin.
        virtual void setNode(QtNodes::NodeDataModel * owner) = 0;

        /* ============================== Code Generation ============================== */

        /// @return : Get the GLSL type (in string) which represents this pin.
        virtual std::string typeToGLSL() = 0;

        // TODO : comment me :)
        virtual std::string defaultValueToGLSL() = 0;

        /// @return : Get name of this pin to std::string.
        virtual std::string nameToGLSL() = 0;
};
}

#endif //SHADERGRAPH_INTERFACE_H
