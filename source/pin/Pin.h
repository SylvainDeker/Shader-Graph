#ifndef SHADERGRAPH_PIN_H
#define SHADERGRAPH_PIN_H

#include <memory>
#include <vector>
#include <string>

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include <core/Core.h>

#include "IPin.h"

#define PIN std::shared_ptr<QtNodes::NodeData>

#define PIN_TEMPLATE_ALL std::vector<EPinType>{TEMPLATE, BOOLEAN, FLOAT, VEC2, VEC3, VEC4}

namespace ShaderGraph
{
    template<typename T>
    class GenType : public QtNodes::NodeData,
                    public IPin
    {
    public:
        /// Default constructor.
        GenType() = default;

        /// Constructor.
        /// @value : The default value of this pin.
        /// @name : The name of this pin.
        /// @owner : The node that contains this pin.
        explicit GenType(T value,
                         QString name,
                         QtNodes::NodeDataModel * owner,
                         EPinType type) :
            m_value(value),
            m_name(name),
            m_owner(owner),
            m_type(type)
        {

        };

        /// The type of this pin. Defined by an ID (string) and a name.
        /// Two pins are connactable if there id are equals.
        QtNodes::NodeDataType type() const override = 0;

        /// Getter : the name of the pin.
        inline const QString& name() const { return m_name; }

        /// Getter : value of this node.
        inline const T &value() const { return m_value; }

        /// Setter : value of this node.
        inline void setValue(const T& value) { m_value = value; }

        /* ==================== IPin ==================== */

        /// @return : true if this pin is connected to an other pin.
        inline bool isConnected() const override { return m_inPin != nullptr; }

        /// Connect this pin.
        inline void connect(PIN inPin) override { m_inPin = inPin; }

        /// Disconnect this pin.
        inline void disconnect() override { m_inPin = nullptr; }

        /// Getter : The connected pin.
        /// @warning : returns nullptr if this pin isn't connected.
        inline std::shared_ptr<QtNodes::NodeData> getConnectedPin() override { return m_inPin; }

        /// Getter : The node which contains this pin.
        inline QtNodes::NodeDataModel * getNode() override { return m_owner; }

        /// Setter : The node which contains this pin.
        inline void setNode(QtNodes::NodeDataModel * owner) override { m_owner = owner; }

        /// @return : Get the GLSL type (in string) which represents this pin.
        std::string typeToGLSL() override = 0;

        // TODO : comment me :)
        std::string defaultValueToGLSL() override = 0;

        /// @return : Get name of this pin to std::string.
        inline std::string nameToGLSL() override { return m_name.toStdString(); }

        inline EPinType getType() override { return m_type; }

        inline void setType(EPinType type) override { m_type = type; };
    private:
        /// The value.
        T m_value;

        /// The name.
        QString m_name;

        /// The connected pin.
        std::shared_ptr<QtNodes::NodeData> m_inPin = nullptr;

        /// The connected node.
        QtNodes::NodeDataModel * m_owner = nullptr;

        EPinType m_type;
    };
}

#endif //SHADERGRAPH_PIN_H
