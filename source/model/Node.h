#ifndef SHADERGRAPH_NODE_H
#define SHADERGRAPH_NODE_H

#include <vector>

#include <QVBoxLayout>
#include <QLayoutItem>
#include <QLayout>

#include <core/Core.h>

#include "Data.h"

#define WIDGET_NODE_SIZE    75
#define IMAGE_NODE_SIZE     150

namespace ShaderGraph
{
    using QtNodes::NodeValidationState;

    class Node : public QtNodes::NodeDataModel
    {
        Q_OBJECT

    public:
        /// Default constructor.
        Node() = default;

        /// Default destructor.
        ~Node() override = default;

        /// Constructor.
        Node(QString name, QString caption) : m_name(name), m_caption(caption) {}

        /// Constructor.
        explicit Node(QString name) : m_name(name), m_caption(name) {}

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

        /// Getter : Current state of this node.
        NodeValidationState validationState() const override { return m_validationState; }

        /// Getter : The error message of this node.
        QString validationMessage() const override { return m_validationMessage; }

        /// Function that display properties in the layout (details)
        virtual void showDetails(QVBoxLayout * layout);

        /// Getter on the position in the layout given by the layout arg in showDetails(layout) function.
        inline size_t getIndexLayout() const { return m_indexLayout; }

        /// Function to know if a layout has already been set up (for details)
        inline bool isLayoutInit() const { return m_layoutInit; }

      protected:

        /// Set a layout
        inline void setLayout(QVBoxLayout * layout) { m_layout = layout; }

        /// Set the index of the layout in the previous function.
        inline void setIndexLayout(size_t idx)
        {
          m_indexLayout = idx;
          m_layoutInit = true;
        }

        /// Getter to the reference to a vector of inputs.
        std::vector<PIN>& inputs()  { return m_inputs;  }

        /// Getter to the reference to a vector of outputs.
        std::vector<PIN>& outputs() { return m_outputs; }

        /// Update the validation state of this node.
        /// @warning : if the node is valid, no message will be displayed.
        inline void updateNodeValidation(NodeValidationState state, QString message = "No message")
        {
            m_validationState = state;
            m_validationMessage = message;
        }

    private:
        QVBoxLayout * m_layout = nullptr;
        size_t m_indexLayout = 0;
        bool m_layoutInit = false;

        QString m_name;
        QString m_caption;

        std::vector<PIN> m_inputs;
        std::vector<PIN> m_outputs;

        QString m_validationMessage = "No message";
        NodeValidationState m_validationState = NodeValidationState::Valid;
    };
}

#endif //SHADERGRAPH_NODE_H
