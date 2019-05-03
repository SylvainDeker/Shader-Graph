#ifndef SHADERGRAPH_NODE_H
#define SHADERGRAPH_NODE_H

#include <list>
#include <vector>
#include <string>
#include <sstream>

#include <QVBoxLayout>
#include <QLayoutItem>
#include <QLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <core/Core.h>

#include "../pin/PinDecl.h"
#include "../detail/DetailDecl.h"

#include "Compilation.h"

#define WIDGET_NODE_SIZE    75
#define IMAGE_NODE_SIZE     150

// Forward declaration of 'QtNodes::Connection'
namespace QtNodes { class Connection; }

namespace ShaderGraph
{
    // function used to avoid float to string conversion with comas from french OS
    template<typename T> std::string to_str(const T a_value, const int precision = 6)
    {
        std::ostringstream out;
        out.precision(precision);
        out << std::fixed << a_value;
        return out.str();
    }

    /// The node ID factory.
    static unsigned int g_nodeId = 0;
    #define GET_NEW_NODE_ID g_nodeId++

    using QtNodes::NodeValidationState;

    class Node : public QtNodes::NodeDataModel
    {
        Q_OBJECT

    public:
        /// Default constructor.
        Node() : m_id(GET_NEW_NODE_ID) {}

        /// Constructor.
        explicit Node(QString name) :
            m_name(name),
            m_caption(name),
            m_id(GET_NEW_NODE_ID)
        {

        }

        /// Constructor.
        Node(QString name, QString caption) :
            m_name(name),
            m_caption(caption),
            m_id(GET_NEW_NODE_ID)
        {

        }

        /// Default destructor.
        ~Node() override = default;

        /* ============================== Nodeeditor - Node props ============================== */

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

        /* ============================== Nodeeditor - Node data ============================== */

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override;

        /// Getter only to the reference to the name.
        QString name() const override;

        /// Getter to the reference to the caption.
        QString caption() const override;

        /* ============================== Nodeeditor - Node error handler ============================== */

        /// Getter : Current state of this node.
        NodeValidationState validationState() const override { return m_validationState; }

        /// Getter : The error message of this node.
        QString validationMessage() const override { return m_validationMessage; }

        /// Update the validation state of this node.
        /// @warning : if the node is valid, no message will be displayed.
        inline void setValidation(NodeValidationState state, QString message = "No message")
        {
            m_validationState = state;
            m_validationMessage = message;
        }

        /* ============================== Code Generation ============================== */

        /// Generate the name of @pin in the GLSL code.
        /// Format : nodeID<nodeID>_<pinname>, with :
        ///     <nodeID> : The id of this node
        ///     <pinname>: The name of the pin, with the convention : lowercase.
        virtual std::string autoName(PIN& pin);

        /// Generate the declarations of this node outputs, for the GLSL code.
        GLSLData outputsToGLSL();

        /// Generate the declarations + initialization of this node inputs, for the GLSL code.
        /// @nodes : A list of nodeID, use to store the visited/generated nodes.
        GLSLData inputsToGLSL(std::list<unsigned int>& nodes);

        /// Generate the "core" of this node, for the GLSL code.
        virtual GLSLData nodeToGLSL() = 0;

        /// Generate the equivalent in GLSL code.
        /// @warning : Will generate the node that it depends on.
        virtual GLSLData toGLSL();

        /// Generate the equivalent in GLSL code.
        /// @warning : Will generate the node that it depends on.
        /// @nodes : A list of nodeID, use to store the visited/generated nodes.
        GLSLData toGLSL(std::list<unsigned int>& nodes);

        /* ============================== Details ============================== */

        /// Show all node's properties in the node panel.
        virtual void showDetails(QTreeWidget * tree);

        /// Hide all node's properties from the node panel.
        virtual void hideDetails(QTreeWidget * tree);

        /// @return : true if this node is showing its properties.
        inline bool isDetailedNode() const { return m_isDetailedNode; }

        /* ============================== Getter/Setter ============================== */

        /// Getter : The node ID.
        inline unsigned int getID() const { return m_id; };

        /// Getter to the reference to a vector of inputs.
        inline std::vector<PIN>& inputs() { return m_inputs; }

        /// Getter to the reference to a vector of outputs.
        inline std::vector<PIN>& outputs() { return m_outputs; }

    public Q_SLOTS:

        void inputConnectionCreated(QtNodes::Connection const& c) override;

        void inputConnectionDeleted(QtNodes::Connection const& c) override;

        void outputConnectionCreated(QtNodes::Connection const& c) override;

        void outputConnectionDeleted(QtNodes::Connection const& c) override;

    private:
        /// True if this node is displayed on the details panel.
        bool m_isDetailedNode = false;

        /// The name of the node.
        QString m_name;

        /// The caption aka a brief description.
        QString m_caption;

        /// The ID of this node.
        /// @note : Each node has a unique id.
        unsigned int m_id;

        /// The internal representation of the input pins.
        std::vector<PIN> m_inputs;

        /// The internal representation of the output pins.
        std::vector<PIN> m_outputs;

        /// The error/warning message.
        /// Equals to "No message" if no error/warning.
        QString m_validationMessage = "No message";

        /// The state (valid, warning, error) state of this node.
        NodeValidationState m_validationState = NodeValidationState::Valid;
    };
}

#endif //SHADERGRAPH_NODE_H
