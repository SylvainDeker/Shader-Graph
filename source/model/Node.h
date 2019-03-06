#ifndef SHADERGRAPH_NODE_H
#define SHADERGRAPH_NODE_H

#include <vector>

#include <core/Core.h>

#include "Data.h"

namespace ShaderGraph
{
    class Node : public QtNodes::NodeDataModel
    {
        Q_OBJECT

    public:
        /// Default constructor.
        Node() = default;

        /// Default destructor.
        ~Node() = default;

        /// Give for a specified port, the number of data.
        /// @portType : the type of the port.
        /// @return : the number of the data.
        unsigned int nPorts(QtNodes::PortType portType) const override;

        /// Give for a specified port, its type.
        /// @portType : the type of the port.
        /// @index : the index of the port.
        /// @return : the type of the data.
        QtNodes::NodeDataType dataType(QtNodes::PortType portType, QtNodes::PortIndex index) const override;

        /// That event happens when an other node is plug-in.
        /// @data : the plugged-in data node.
        /// @index : the index of the port.
        void setInData(std::shared_ptr<QtNodes::NodeData> data, QtNodes::PortIndex index) override;

        /// The output of this node, at the specified index.
        /// @index : the index of the port.
        /// @return : a shared point to the data to retrieve.
        std::shared_ptr<QtNodes::NodeData> outData(QtNodes::PortIndex index) override;

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override;

        /// Getter only to the reference to the name.
        QString name() const override;

        /// Getter to the reference to the caption.
        QString caption() const override;

    protected:

        Node(QString name, QString caption) : m_name(name), m_caption(caption) {}
        Node(QString name) : m_name(name), m_caption(name) {}

        std::vector<PIN>& inputs()  { return m_inputs;  }
        std::vector<PIN>& outputs() { return m_outputs; }

    private:
        QString m_name;
        QString m_caption;

        std::vector<PIN> m_inputs;
        std::vector<PIN> m_outputs;
    };
}

#endif //SHADERGRAPH_NODE_H
