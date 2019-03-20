#include "Node.h"

namespace ShaderGraph
{
    /// Give for a specified port, the number of data.
    /// @portType : the type of the port.
    /// @return : the number of the data.
    unsigned int Node::nPorts(QtNodes::PortType portType) const
    {
        switch (portType)
        {
            case QtNodes::PortType::In :    return static_cast<unsigned int>(m_inputs.size());
            case QtNodes::PortType::Out :   return static_cast<unsigned int>(m_outputs.size());
            default :                       break;
        }
        return 0;
    }

    /// Give for a specified port, its type.
    /// @portType : the type of the port.
    /// @index : the index of the port.
    /// @return : the type of the data.
    QtNodes::NodeDataType Node::dataType(QtNodes::PortType portType, QtNodes::PortIndex index) const
    {
        switch (portType)
        {
        case QtNodes::PortType::In :    return m_inputs[index]->type();
        case QtNodes::PortType::Out :   return m_outputs[index]->type();
        default :                       break;
        }
        return QtNodes::NodeDataType();
    }

    /// That event happens when an other node is plug-in.
    /// @data : the plugged-in data node.
    /// @index : the index of the port.
    void Node::setInData(std::shared_ptr<QtNodes::NodeData> data, QtNodes::PortIndex index)
    {
        if (index >= 0 || index < (int) m_outputs.size())
        {
            auto input = std::dynamic_pointer_cast<IConnectable>(data);
            auto pin   = std::dynamic_pointer_cast<IConnectable>(m_inputs[index]);

            if (pin != nullptr)
            {
                if (input == nullptr && pin->isConnected()) pin->disconnect();
                else pin->connect(data);
            }
            else LOG_ERROR("ShaderGraph::Node::setInData : Invalid pin");
        }
        else LOG_ERROR("ShaderGraph::Node::setInData : Invalid port index");
    }

    /// The output of this node, at the specified index.
    /// @index : the index of the port.
    /// @return : a shared point to the data to retrieve.
    std::shared_ptr<QtNodes::NodeData> Node::outData(QtNodes::PortIndex index)
    {
        if (index >= 0 || index < (int) m_outputs.size()) return m_outputs[index];
        LOG_ERROR("ShaderGraph::Node::outData : Invalid port index");
        return nullptr;
    }

    /// Specified the embedded widget in the Node.
    /// @return : the widget.
    QWidget * Node::embeddedWidget()
    {
        return nullptr;
    }

    /// Getter only to the reference to the name.
    QString Node::name() const
    {
        return m_name;
    }

    /// Getter to the reference to the caption.
    QString Node::caption() const
    {
        return m_caption;
    }

    // FIXME : too much dynamic_cast
    void Node::updateLayerId()
    {
        unsigned int layerID = 0;

        for (PIN data : m_inputs)
        {
            auto pin = std::dynamic_pointer_cast<IConnectable>(data);
            if (pin)
            {
                if (pin->isConnected())
                {
                    auto node = std::dynamic_pointer_cast<IParsable>(pin->getConnectedPin());
                    if (node)
                    {
                        auto layerableNode = dynamic_cast<ILayerable*>(node->getNode());

                        if (layerableNode) layerID = std::max(layerID, layerableNode->getLayer() + 1);
                        else LOG_ERROR("Node::updateLayerId : invalid connected pin");
                    }
                    else LOG_ERROR("Node::updateLayerId : invalid connected pin");
                }
            }
            else LOG_ERROR("Node::updateLayerId : invalid pin");
        }

        m_layer = layerID;
    }

    /// Function that display info in the layout (details)
    void Node::showDetails(QVBoxLayout * layout)
    {
        for (int i = 0; i < layout->count(); i++)
        {
            layout->itemAt(i)->widget()->setVisible(false);
        }
    }


}
