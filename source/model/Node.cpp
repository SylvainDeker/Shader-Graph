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
        if (index >= 0 || index < (int) m_inputs.size())
        {
            if (!data)
            {
                LOG_ERROR("Node::setInData : nullptr");
            }

            auto input = std::dynamic_pointer_cast<IPin>(data);
            auto pin   = std::dynamic_pointer_cast<IPin>(m_inputs[index]);

            assert(pin != nullptr);

            if (!input || pin->isConnected())
            {
                pin->disconnect();
            }
            else
            {
                pin->connect(data);
            }
        }
        else LOG_ERROR("ShaderGraph::Node::setInData : Invalid port index");
    }

    /// The output of this node, at the specified index.
    /// @index : the index of the port.
    /// @return : a shared point to the data to retrieve.
    std::shared_ptr<QtNodes::NodeData> Node::outData(QtNodes::PortIndex index)
    {
        if (index >= 0 || index < (int) m_outputs.size())
        {
            auto output = m_outputs[index];

            if (output == nullptr)
            {
                LOG_WARN("Node::outData : An output data is null");
            }

            return output;
        }

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

    void Node::showDetails(QTreeWidget * tree)
    {
        (void) tree;
        m_isDetailedNode = true;
    }

    void Node::hideDetails(QTreeWidget * tree)
    {
        (void) tree;
        m_isDetailedNode = false;
    }

    /// Generate the name of @pin in the GLSL code.
    /// Format : nodeID<nodeID>_<pinname>, with :
    ///     <nodeID> : The id of this node
    ///     <pinname>: The name of the pin, with the convention : lowercase.
    std::string Node::autoName(PIN pin)
    {
        std::string pinName = pin->type().name.toStdString();
        pinName.erase(remove_if(pinName.begin(), pinName.end(), isspace), pinName.end());
        std::transform(pinName.begin(), pinName.end(), pinName.begin(), ::tolower);

        return "id" + std::to_string(m_id) + "_" + pin->type().name.toStdString();
    }

    std::vector<PIN>& Node::inputs()
    {
        return m_inputs;
    }

    std::vector<PIN>& Node::outputs()
    {
        return m_outputs;
    }

    std::vector<PIN>& Node::details()
    {
        return m_details;
    }

    std::string Node::outputsToGLSL()
    {
        std::string code = "";
        for (PIN output : m_outputs)
        {
            // Get the pin interface
            auto pin = dynamic_cast<IPin*>(output.get());
            if (pin)
            {
                std::string line = pin->typeToGLSL()         + " " +
                                   autoName(output)          + "=" +
                                   pin->defaultValueToGLSL() + ";" ;

                code += line + "\n";
            }
            else LOG_ERROR("Node::outputsToString : Invalid pin");
        }
        return code;
    }

    std::string Node::inputsToGLSL(std::list<unsigned int>& nodes)
    {
        std::string code = "";
        for (PIN input : m_inputs)
        {
            // Get the pin interface
            auto pin = dynamic_cast<IPin*>(input.get());
            if (pin)
            {
                std::string value = "INVALID_VALUE";

                if (pin->isConnected())
                {
                    std::shared_ptr<QtNodes::NodeData> connectedNodeData = pin->getConnectedPin();
                    auto connectedPin = dynamic_cast<IPin *>(connectedNodeData.get());

                    if (connectedPin == nullptr)
                    {
                        LOG_ERROR("Parsing : A pin is connected to an invalid pin");
                        // TODO : parsing error handler
                    }
                    
                    auto connectedNode = dynamic_cast<Node*>(connectedPin->getNode());
                                        
                    code += connectedNode->toGLSL(nodes) + "\n";
                    nodes.push_back(connectedNode->getID());

                    value = "id" + std::to_string(connectedNode->getID()) + "_" + connectedPin->nameToGLSL();
                }
                else value = pin->defaultValueToGLSL();
                
                std::string line = pin->typeToGLSL() + " " +
                                   autoName(input)   + "=" +
                                   value             + ";" ;

                code += line + "\n";
            }
            else LOG_ERROR("Node::outputsToString : Invalid pin");
        }
        return code;
    }

    std::string Node::toGLSL()
    {
        std::string glslCode = "";
        std::list<unsigned int> nodes;
        nodes.push_back(m_id);
        glslCode += inputsToGLSL(nodes);
        glslCode += outputsToGLSL();
        glslCode += nodeToGLSL();

        return glslCode;
    }

    std::string Node::toGLSL(std::list<unsigned int> nodes)
    {
        std::string glslCode = "";

        bool isFound = std::find(nodes.begin(), nodes.end(), m_id) != nodes.end();

        if (!isFound)
        {
            nodes.push_back(m_id);
            glslCode += inputsToGLSL(nodes);
            glslCode += outputsToGLSL();
            glslCode += nodeToGLSL();
        }

        return glslCode;
    }

}
