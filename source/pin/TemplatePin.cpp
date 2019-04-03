#include "TemplatePin.h"

#include <memory>
#include <cassert>

#include <core/Core.h>

#include "model/Node.h"

namespace ShaderGraph
{
    /// Connect this pin.
    void Template::connect(PIN inPin)
    {
        auto pin = std::dynamic_pointer_cast<IPin>(inPin);
        assert(pin != nullptr);

        auto node = dynamic_cast<Node*>(getNode());
        assert(node != nullptr);

        EPinType connectedPinType = pin->getType();

        if (!isConnectable(connectedPinType))
        {
            node->updateNodeValidation(NodeValidationState::Error, "Unexpected Connection");
            onConnectionInvalid(connectedPinType);
            setPinType(EPinType::TEMPLATE);
        }
        else
        {
            node->updateNodeValidation(NodeValidationState::Valid);
            Pin::connect(inPin);
            setPinType(pin->getType());
        }
    }

    /// Getter : The connected pin.
    /// @warning : returns nullptr if this pin isn't connected.
    std::shared_ptr<QtNodes::NodeData> Template::getConnectedPin()
    {

        auto pin = std::dynamic_pointer_cast<IPin>(m_pin);

        assert(pin != nullptr);

        return pin->getConnectedPin();
    }

    /// Setter : The node which contains this pin.
    void Template::setNode(QtNodes::NodeDataModel * owner)
    {
        auto pin = std::dynamic_pointer_cast<IPin>(m_pin);

        assert(pin != nullptr);

        pin->setNode(owner);
    }

    /// @return : Get the GLSL type (in string) which represents this pin.
    std::string Template::typeToGLSL()
    {
        auto pin = std::dynamic_pointer_cast<IPin>(m_pin);

        assert(pin != nullptr);

        return pin->typeToGLSL();
    }

    std::string Template::defaultValueToGLSL()
    {
        auto pin = std::dynamic_pointer_cast<IPin>(m_pin);

        assert(pin != nullptr);

        return pin->defaultValueToGLSL();
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

            switch (type)
            {
                case EPinType::BOOLEAN :
                    m_pin = std::make_shared<Boolean>(name(), getNode());
                    m_typeId = "Boolean";
                    break;

                case EPinType::FLOAT :
                    m_pin = std::make_shared<Float>(name(), getNode());
                    m_typeId = "Float";
                    break;

                case EPinType::VEC2 :
                    m_pin = std::make_shared<Vector2>(name(), getNode());
                    m_typeId = "Vector2";
                    break;

                case EPinType::VEC3 :
                    m_pin = std::make_shared<Vector3>(name(), getNode());
                    m_typeId = "Vector3";
                    break;

                case EPinType::VEC4 :
                    m_pin = std::make_shared<Vector4>(name(), getNode());
                    m_typeId = "Vector4";
                    break;

                default :
                    LOG_ERROR("Template::setPin : Invalid pin type");
                    break;
            }

            setType(type);
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