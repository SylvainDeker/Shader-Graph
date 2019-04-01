#include "TemplatePin.h"

#include <memory>

#include "model/Node.h"

namespace ShaderGraph
{
    /// Connect this pin.
    void Template::connect(PIN inPin)
    {
        auto pin = std::dynamic_pointer_cast<IPin>(inPin);

        if (pin == nullptr)
        {
            LOG_ERROR("Template::connect : the connected node doesn't implement IPin");
        } else
        {
            EPinType connectedPinType = pin->getType();

            if (!isConnectable(connectedPinType))
            {
                onConnectionInvalid(connectedPinType);
            }
            else
            {
                GenType::connect(inPin);
                setPinType(pin->getType());
            }
        }
    }

    /// Getter : The connected pin.
    /// @warning : returns nullptr if this pin isn't connected.
    std::shared_ptr<QtNodes::NodeData> Template::getConnectedPin()
    {
        auto pin = dynamic_cast<IPin*>(m_pin);

        if (pin == nullptr)
        {
            LOG_ERROR("Template:getConnectedPin : This pin doesn't implement IPin");
            return nullptr;
        }
        else
        {
            return pin->getConnectedPin();
        }
    }

    /// Setter : The node which contains this pin.
    void Template::setNode(QtNodes::NodeDataModel * owner)
    {
        auto pin = dynamic_cast<IPin*>(m_pin);

        if (pin == nullptr)
        {
            LOG_ERROR("Template:setNode : This pin doesn't implement IPin");
        }
        else
        {
            pin->setNode(owner);
        }
    }

    /// @return : Get the GLSL type (in string) which represents this pin.
    std::string Template::typeToGLSL()
    {
        auto pin = dynamic_cast<IPin*>(m_pin);

        if (pin == nullptr)
        {
            LOG_ERROR("Template:typeToGLSL : This pin doesn't implement IPin");
            return "FATAL ERROR";
        }
        else
        {
            return pin->typeToGLSL();
        }
    }

    std::string Template::defaultValueToGLSL()
    {
        auto pin = dynamic_cast<IPin*>(m_pin);

        if (pin == nullptr)
        {
            LOG_ERROR("Template:defaultValueToGLSL : This pin doesn't implement IPin");
            return "FATAL ERROR";
        }
        else
        {
            return pin->defaultValueToGLSL();
        }
    }

    void Template::setPinType(EPinType type)
    {
        if (type == EPinType::TEMPLATE)
        {
            LOG_DEBUG("Template::setPin : Template type");
        }
        else if (!isConnectable(type))
        {
            onConnectionInvalid(type);
            return;
        }
        else
        {
            LOG_DEBUG("Template::setPin : Set the template to : {0}", pinTypeToString(type));

            setType(type); // Set the new type.

            delete m_pin; // delete the old value of @m_pin, will be reset after.

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

            forceUpdateNode(type);
        }
    }

    void Template::forceUpdatePin(PIN pin, EPinType type)
    {
        auto iPin  = std::dynamic_pointer_cast<IPin>(pin);
        auto tPin = std::dynamic_pointer_cast<Template>(pin);

        if (pin != nullptr)
        {
            EPinType pinType = iPin->getType();

            if (tPin != nullptr &&
                tPin->getTemplateID() == m_templateID &&
                pinType != type)
            {
                if (tPin->isConnectable(type)) tPin->setPinType(type);
                else LOG_CRITICAL("Template::updateNode : Design error...");
            }
        }
        else
        {
            LOG_ERROR("Template::updateNode : A pin doesn't implement IPin");
        }
    }

    void Template::forceUpdateNode(EPinType type)
    {
        auto node = dynamic_cast<Node*>(getNode());
        for (PIN in : node->inputs()) forceUpdatePin(in, type);
        for (PIN out : node->outputs()) forceUpdatePin(out, type);
    }

    void Template::onConnectionInvalid(EPinType type)
    {
        LOG_ERROR("Template::setPin : Invalid pin type : the IN type can be :");
        for (EPinType connectableType : m_connectableTypes)
        {
            LOG_ERROR(pinTypeToString(connectableType));
        }
        LOG_ERROR("And not : {0}.", pinTypeToString(type));
    }
}