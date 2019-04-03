#ifndef SHADERGRAPH_INTERFACE_H
#define SHADERGRAPH_INTERFACE_H

namespace ShaderGraph
{
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
        
        virtual std::string valueToGLSL() = 0;

        /// @return : Get name of this pin to std::string.
        virtual std::string nameToGLSL() = 0;
};
}

#endif //SHADERGRAPH_INTERFACE_H
