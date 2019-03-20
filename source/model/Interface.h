#ifndef SHADERGRAPH_INTERFACE_H
#define SHADERGRAPH_INTERFACE_H

namespace ShaderGraph
{
    /* ============================== Node Interfaces ============================== */

    class ILayerable
    {
    public:
        /// Default constructor.
        ILayerable() = default;

        /// Default destructor.
        virtual ~ILayerable() = default;

        /// Getter : Current layer id of this node.
        virtual unsigned int getLayer() const = 0;

        /// Setter : Current layer id of this node.
        virtual void setLayer(unsigned int layer) = 0;

        // TODO : comment me :)
        virtual void updateLayerId() = 0;
    };
    
    /* ============================== Pin Interfaces ============================== */
    
    class IConnectable
    {
    public:
        /// Default constructor.
        IConnectable() = default;

        /// Default destructor.
        virtual ~IConnectable() = default;

        /// @return : true if this pin is connected to an other pin.
        virtual bool isConnected() const = 0;

        /// Connect the pin to interface to an other pin.
        virtual void connect(std::shared_ptr<QtNodes::NodeData> inPin) = 0;

        /// Disconnect this pin if it was connected.
        virtual void disconnect() = 0;

        /// Getter : The connected pin.
        /// @return : nullptr if this pin isn't connected to an other pin.
        virtual std::shared_ptr<QtNodes::NodeData> getConnectedPin() = 0;
    };

    class IParsable
    {
    public:
        /// Default constructor.
        IParsable() = default;

        /// Default destructor.
        virtual ~IParsable() = default;

        /// Setter : The node that "owns" this pin.
        virtual void setNode(QtNodes::NodeDataModel * owner) = 0;

        /// Getter : The node that "owns" this pin.
        virtual QtNodes::NodeDataModel * getNode() = 0;
    };
}

#endif //SHADERGRAPH_INTERFACE_H
