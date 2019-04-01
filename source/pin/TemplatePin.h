#ifndef SHADERGRAPH_TEMPLATEPIN_H
#define SHADERGRAPH_TEMPLATEPIN_H

#include <core/Core.h>

#include "Pin.h"

#include "BooleanPin.h"
#include "FloatPin.h"
#include "VectorPin.h"

namespace ShaderGraph
{
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

        virtual ~Template()
        {
            delete m_pin;
        }

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

            LOG_DEBUG("Template::setPin : Set the template to : {0}", pinTypeToString(type));

            setType(type);

            delete m_pin;

            switch (type)
            {
                case EPinType::BOOLEAN :
                    m_pin = new Boolean(name(), getNode());
                    break;

                case EPinType::FLOAT :
                    m_pin = new Float(name(), getNode());
                    break;

                case EPinType::VEC2 :
                    m_pin = new Vector2(name(), getNode());
                    break;

                case EPinType::VEC3 :
                    m_pin = new Vector3(name(), getNode());
                    break;

                case EPinType::VEC4 :
                    m_pin = new Vector4(name(), getNode());
                    break;

                default :
                    LOG_ERROR("Template::setPin : Invalid pin type");
                    break;
            }
        }

    private:

        std::vector<EPinType> m_connectableTypes;

        QtNodes::NodeData * m_pin = nullptr;
    };
}

#endif //SHADERGRAPH_TEMPLATEPIN_H
