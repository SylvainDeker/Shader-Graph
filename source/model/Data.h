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
                    public IPin
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
    private:
        T m_value;
        QString m_name;

        unsigned int m_inPinIndex;
        std::shared_ptr<QtNodes::NodeData> m_inPin = nullptr;

        QtNodes::NodeDataModel * m_owner = nullptr;
    };

    class Boolean : public GenType<bool>
    {
    public:
        /// Default constructor.
        Boolean(QString name = "Boolean", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<bool>(false, name, owner)
        {

        };

        /// Constructor.
        Boolean(bool value, QString name = "Boolean", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<bool>(value, name, owner)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Bool", name()};
        }

        /// @return : Get the GLSL type (in string) which represents this pin.
        std::string typeToGLSL() override { return "bool"; }

        // TODO : comment me :)
        std::string defaultValueToGLSL() override { return "false"; }
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
        Float(float value, QString name = "Float", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<float>(value, name, owner)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Float", name()};
        }

        /// @return : Get the GLSL type (in string) which represents this pin.
        std::string typeToGLSL() override { return "float"; }

        // TODO : comment me :)
        std::string defaultValueToGLSL() override { return "0.0f"; }
    };

    class Vector2 : public GenType<glm::vec2>
    {
    public:
        /// Default constructor.
        Vector2(QString name = "Vector2D", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec2>(glm::vec2(0.0f), name, owner)
        {

        };

        /// Constructor.
        Vector2(glm::vec2 value, QString name = "Vector2D", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec2>(value, name, owner)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Vector2", name()};
        }

        /// @return : Get the GLSL type (in string) which represents this pin.
        std::string typeToGLSL() override { return "vec2"; }

        // TODO : comment me :)
        std::string defaultValueToGLSL() override { return "vec2(0.0f)"; }
    };

    class Vector3 : public GenType<glm::vec3>
    {
    public:
        /// Default constructor.
        Vector3(QString name = "Vector3D", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec3>(glm::vec3(0.0f), name, owner)
        {

        };

        /// Constructor.
        Vector3(glm::vec3 value, QString name = "Vector3D", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec3>(value, name, owner)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Vector3", name()};
        }

        /// @return : Get the GLSL type (in string) which represents this pin.
        std::string typeToGLSL() override { return "vec3"; }

        // TODO : comment me :)
        std::string defaultValueToGLSL() override { return "vec3(0.0f)"; }
    };

    class Vector4 : public GenType<glm::vec4>
    {
    public:
        /// Default constructor.
        Vector4(QString name = "Vector4D", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec4>(glm::vec4(0.0f), name, owner)
        {

        };

        /// Constructor.
        Vector4(glm::vec4 value, QString name = "Vector4D", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec4>(value, name, owner)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Vector4", name()};
        }

        /// @return : Get the GLSL type (in string) which represents this pin.
        std::string typeToGLSL() override { return "vec4"; }

        // TODO : comment me :)
        std::string defaultValueToGLSL() override { return "vec4(0.0f)"; }
    };
}

#endif //SHADERGRAPH_DATA_H
