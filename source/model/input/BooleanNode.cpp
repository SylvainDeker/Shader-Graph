//
// Created by Valentin on 2019-02-14.
//

#include "BooleanNode.h"

#include "../Data.h"

namespace ShaderGraph
{
    /// Constructor.
    BooleanNode::BooleanNode()
    {
        m_name      = "BooleanNode";
        m_caption   = "BooleanNode";

        LOG_DEBUG("BooleanNode !!");
    }

    /// Give for a specified port, the number of data.
    /// @portType : the type of the port.
    /// @return : the number of the data.
    unsigned int BooleanNode::nPorts(QtNodes::PortType portType) const
    {
        switch (portType)
        {
            case QtNodes::PortType::Out :   return 1;
            default :                       break;
        }
        return 0;
    }

    /// Give for a specified port, its type.
    /// @portType : the type of the port.
    /// @index : the index of the port.
    /// @return : the type of the data.
    QtNodes::NodeDataType BooleanNode::dataType(QtNodes::PortType portType, QtNodes::PortIndex index) const
    {
        (void) index;

        switch (portType)
        {
            case QtNodes::PortType::Out :   return BooleanNodeData().type();
            default :                       break;
        }
        return QtNodes::NodeDataType();
    }

    /// That event happens when an other node is plug-in.
    /// @data : the plugged-in data node.
    /// @index : the index of the port.
    void BooleanNode::setInData(std::shared_ptr<QtNodes::NodeData> data, QtNodes::PortIndex index)
    {
        (void) data;
        (void) index;
    }

    /// The output of this node, at the specified index.
    /// @index : the index of the port.
    /// @return : a shared point to the data to retrieve.
    std::shared_ptr<QtNodes::NodeData> BooleanNode::outData(QtNodes::PortIndex index)
    {
        (void) index;
        return std::make_shared<BooleanNodeData>();
    }

    /// Specified the embedded widget in the Node.
    /// @return : the widget.
    QWidget * BooleanNode::embeddedWidget()
    {
        return nullptr;
    }
}