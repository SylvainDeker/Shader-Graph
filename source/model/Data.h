#ifndef SHADERGRAPH_DATA_H
#define SHADERGRAPH_DATA_H

#include <memory>

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include "Interface.h"

#define PIN std::shared_ptr<QtNodes::NodeData>

namespace ShaderGraph
{
    template<typename T>
    class GenType : public QtNodes::NodeData,
                    public IConnectable,
                    public IParsable
    {
    public:
        /// Default constructor.
        GenType() = default;

        /// Constructor.
        /// @value : The default value of this pin.
        /// @name : The name of this pin.
        /// @owner : The node that contains this pin.
        GenType(T value, QString name, QtNodes::NodeDataModel * owner) :
            m_value(value),
            m_name(name),
            m_owner(owner)
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

        /* ==================== IConnectable ==================== */

        /// @return : true if this pin is connected to an other pin.
        bool isConnected() const override { return m_inPin != nullptr; }

        /// Connect this pin to an other pin.
        void connect(PIN inPin) override
        {
            m_inPin = inPin;

            auto * node = dynamic_cast<ILayerable*>(m_owner);

            if (node) node->updateLayerId();
            else LOG_ERROR("IConnectable::GenType::connect : reference to owner invalid");
        }

        /// Disconnect this pin.
        void disconnect() override
        {
            m_inPin = nullptr;

            auto * node = dynamic_cast<ILayerable*>(m_owner);

            if (node) node->updateLayerId();
            else LOG_ERROR("IConnectable::GenType::disconnect : reference to owner invalid");
        }

        /// Getter : The connected pin.
        /// @return : nullptr if this pin isn't connected to an other pin.
        inline std::shared_ptr<QtNodes::NodeData> getConnectedPin() override { return m_inPin; }

        /* ==================== IParsable ==================== */

        /// Getter : The node that "owns" this pin.
        QtNodes::NodeDataModel * getNode() override { return m_owner; }

        /// Setter : The node that "owns" this pin.
        void setNode(QtNodes::NodeDataModel * owner) override { m_owner = owner; }


    private:
        T m_value;
        QString m_name;

        std::shared_ptr<QtNodes::NodeData> m_inPin = nullptr;
        QtNodes::NodeDataModel * m_owner = nullptr;
    };

    class Boolean : public GenType<bool>
    {
    public:
        /// Default constructor.
        Boolean(QString name = "Bool", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<bool>(false, name, owner)
        {

        };

        /// Constructor.
        Boolean(bool value, QtNodes::NodeDataModel * owner, QString name = "bool") :
            GenType<bool>(value, name, owner)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Bool", name()};
        }
    };

    class Float : public GenType<float>
    {
    public:
        /// Default constructor.
        Float(QString name = "Float", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<float>(0.0f, name, owner)
        {

        };

        /// Constructor.
        Float(float value, QtNodes::NodeDataModel * owner, QString name = "float") :
            GenType<float>(value, name, owner)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Float", name()};
        }
    };

    class Vector2 : public GenType<glm::vec2>
    {
    public:
        /// Default constructor.
        Vector2(QString name = "vec2", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec2>(glm::vec2(0.0f), name, owner)
        {

        };

        /// Constructor.
        Vector2(glm::vec2 value, QtNodes::NodeDataModel * owner, QString name = "vec2") :
            GenType<glm::vec2>(value, name, owner)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Vector2", name()};
        }
    };

    class Vector3 : public GenType<glm::vec3>
    {
    public:
        /// Default constructor.
        Vector3(QString name = "vec3", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec3>(glm::vec3(0.0f), name, owner)
        {

        };

        /// Constructor.
        Vector3(glm::vec3 value, QtNodes::NodeDataModel * owner, QString name = "vec3") :
            GenType<glm::vec3>(value, name, owner)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Vector3", name()};
        }
    };

    class Vector4 : public GenType<glm::vec4>
    {
    public:
        /// Default constructor.
        Vector4(QString name = "vec4", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec4>(glm::vec4(0.0f), name, owner)
        {

        };

        /// Constructor.
        Vector4(glm::vec4 value, QtNodes::NodeDataModel * owner, QString name = "vec4") :
            GenType<glm::vec4>(value, name, owner)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Vector4", name()};
        }
    };
}

#endif //SHADERGRAPH_DATA_H
