#ifndef SHADERGRAPH_DATA_H
#define SHADERGRAPH_DATA_H

#include <memory>

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#define PIN std::shared_ptr<QtNodes::NodeData>

namespace ShaderGraph
{
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
        virtual void connect(PIN inPin) = 0;

        /// Disconnect this pin.
        virtual void disconnect() = 0;
    };

    template<typename T>
    class GenType : public QtNodes::NodeData, public IConnectable
    {
    public:
        /// Default constructor.
        GenType() = default;

        /// Constructor.
        GenType(T value, QString name) : m_value(value), m_name(name) {};

        /// Getter : the name of the pin.
        inline const QString& name() const { return m_name; }

        /// Getter : value of this node.
        inline const T &value() const { return m_value; }

        /// Setter : value of this node.
        inline void setValue(const T& value) { m_value = value; }

        /// @return : true if this pin is connected to an other pin.
        bool isConnected() const override { return m_inPin == nullptr; }

        /// Connect this pin to an other pin.
        void connect(PIN inPin) override { m_inPin = inPin; }

        /// Disconnect this pin.
        void disconnect() override { m_inPin = nullptr; }

        QtNodes::NodeDataType type() const override = 0;

    private:
        T m_value;
        QString m_name;

        std::shared_ptr<QtNodes::NodeData> m_inPin = nullptr;
    };

    class Boolean : public GenType<bool>
    {
    public:
        /// Default constructor.
        Boolean(QString name = "bool") : GenType<bool>(false, name){};

        /// Constructor.
        Boolean(bool value, QString name = "bool") : GenType<bool>(value, name) {};

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
        Float(QString name = "float") : GenType<float>(0.0f, name) {};

        /// Constructor.
        Float(float value, QString name = "float") : GenType<float>(value, name) {};

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
        Vector2(QString name = "vec2") : GenType<glm::vec2>(glm::vec2(0.0f), name) {};

        /// Constructor.
        Vector2(glm::vec2 value, QString name = "vec2") : GenType<glm::vec2>(value, name) {};

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
        Vector3(QString name = "vec3") : GenType<glm::vec3>(glm::vec3(0.0f), name) {};

        /// Constructor.
        Vector3(glm::vec3 value, QString name = "vec3") : GenType<glm::vec3>(value, name) {};

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
        Vector4(QString name = "vec4") : GenType<glm::vec4>(glm::vec4(0.0f), name) {};

        /// Constructor.
        Vector4(glm::vec4 value, QString name = "vec4") : GenType<glm::vec4>(value, name) {};

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Vector4", name()};
        }
    };
}

#endif //SHADERGRAPH_DATA_H
