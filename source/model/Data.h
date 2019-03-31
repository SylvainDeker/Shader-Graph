#ifndef SHADERGRAPH_DATA_H
#define SHADERGRAPH_DATA_H

#include <memory>
#include <vector>
#include <string>

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include "Interface.h"

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

    class Boolean : public GenType<bool>
    {
    public:
        /// Default constructor.
        explicit Boolean(QString name = "Boolean", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<bool>(false, name, owner, EPinType::BOOLEAN)
        {

        };

        /// Constructor.
        explicit Boolean(bool value, QString name = "Boolean", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<bool>(value, name, owner, EPinType::BOOLEAN)
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
        explicit Float(QString name = "Float", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<float>(0.0f, name, owner, EPinType::FLOAT)
        {

        };

        /// Constructor.
        explicit Float(float value, QString name = "Float", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<float>(value, name, owner, EPinType::FLOAT)
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
        explicit Vector2(QString name = "Vector2D", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec2>(glm::vec2(0.0f), name, owner, EPinType::VEC2)
        {

        };

        /// Constructor.
        explicit Vector2(glm::vec2 value, QString name = "Vector2D", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec2>(value, name, owner, EPinType::VEC2)
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
        explicit Vector3(QString name = "Vector3D", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec3>(glm::vec3(0.0f), name, owner, EPinType::VEC3)
        {

        };

        /// Constructor.
        explicit Vector3(glm::vec3 value, QString name = "Vector3D", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec3>(value, name, owner, EPinType::VEC3)
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
        explicit Vector4(QString name = "Vector4D", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec4>(glm::vec4(0.0f), name, owner, EPinType::VEC4)
        {

        };

        /// Constructor.
        explicit Vector4(glm::vec4 value, QString name = "Vector4D", QtNodes::NodeDataModel * owner = nullptr) :
            GenType<glm::vec4>(value, name, owner, EPinType::VEC4)
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

    class Template : public GenType<int>
    {
    public:
        /// Default constructor.
        explicit Template(EPinType type,
                          QString name = "T",
                          QtNodes::NodeDataModel * owner = nullptr) :
                GenType<int>(0, name, owner, EPinType::TEMPLATE),
                m_connectableTypes(std::vector<EPinType>{type})
        {
            setPinType(type);
        };

        /// Default constructor.
        explicit Template(std::vector<EPinType> connectableTypes = PIN_TEMPLATE_ALL,
                          QString name = "T",
                          QtNodes::NodeDataModel * owner = nullptr) :
                GenType<int>(0, name, owner, EPinType::TEMPLATE),
                m_connectableTypes(connectableTypes)
        {

        };

        inline bool checkType(EPinType type)
        {
            auto types = m_connectableTypes; // alias
            return (std::find(types.begin(), types.end(), type) != types.end());
        }

        /// Connect this pin.
        inline void connect(PIN inPin) override
        {
            auto pin = std::dynamic_pointer_cast<IPin>(inPin);

            if (pin == nullptr)
            {
                LOG_ERROR("Template::connect : the connected node doesn't implement IPin");
            }
            else
            {
                if (!checkType(pin->getType()))
                {
                    LOG_ERROR("Template::setPin : Invalid pin type : the IN type can be :");
                    for (EPinType connectableType : m_connectableTypes)
                    {
                        LOG_ERROR(pinTypeToString(connectableType));
                    }
                    LOG_ERROR("And not : {0}.", pinTypeToString(pin->getType()));
                }
                else
                {
                    GenType::connect(inPin);
                }
            }
        }

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Template", name()};
        }

        /// @return : Get the GLSL type (in string) which represents this pin.
        inline std::string typeToGLSL() override
        {
            auto pin = dynamic_cast<IPin*>(m_pin);

            if (!pin)
            {
                LOG_ERROR("Template:typeToGLSL : This pin doesn't implement IPin");
                return "FATAL ERROR";
            }

            return pin->typeToGLSL();
        }

        // TODO : comment me :)
        std::string defaultValueToGLSL() override
        {
            auto pin = dynamic_cast<IPin*>(m_pin);

            if (!pin)
            {
                LOG_ERROR("Template:typeToGLSL : This pin doesn't implement IPin");
                return "FATAL ERROR";
            }

            return pin->defaultValueToGLSL();
        }

        inline QtNodes::NodeData * getPin() { return m_pin; }

        inline void setPinType(EPinType type)
        {
            if (!checkType(type))
            {
                LOG_ERROR("Template::setPin : Invalid pin type : the IN type can be :");
                for (EPinType connectableType : m_connectableTypes)
                {
                    LOG_ERROR(pinTypeToString(connectableType));
                }
                LOG_ERROR("And not : {0}.", pinTypeToString(type));

                return;
            }

            LOG_DEBUG("Set the template to : {0}", pinTypeToString(type));

            setType(type);
        }

    private:

        std::vector<EPinType> m_connectableTypes;

        QtNodes::NodeData * m_pin = nullptr;
    };
}

#endif //SHADERGRAPH_DATA_H
