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
            node->setValidation(NodeValidationState::Error, "Unexpected Connection");
            onConnectionInvalid(connectedPinType);
            setBindedType(EPinType::TEMPLATE);
        }
        else
        {
            node->setValidation(NodeValidationState::Valid);
            Pin::connect(inPin);
            setBindedType(pin->getType());
        }
    }

    /// Disconnect this pin.
    void Template::disconnect()
    {
        Pin::disconnect();

        auto node = dynamic_cast<Node*>(getNode());

        // Note : Only for debug --
        // knowing the number of connected pin is useless otherwise.
        unsigned int connectedPinsCount = 0;

        assert(node != nullptr);

        for (PIN in : node->inputs())
        {
            auto pin = std::dynamic_pointer_cast<Template>(in);

            if (pin && pin->getTemplateID() == m_templateID && pin->isConnected())
            {
                ++connectedPinsCount;
            }
        }

        LOG_DEBUG("Template::disconnect : ");
        LOG_DEBUG("{0} pin constrain the type to {1}", connectedPinsCount, pinTypeToString(getType()));

        if (connectedPinsCount == 0)
        {
            for (PIN sibling : getSiblings())
            {
                auto pin = std::dynamic_pointer_cast<Template>(sibling);
                assert(pin != nullptr);
                pin->setBindedType(EPinType::TEMPLATE);
            }

            LOG_DEBUG("Template::disconnect : ");
            LOG_DEBUG("Type reset");
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

    void Template::setBindedType(EPinType type)
    {
        if (type == EPinType::TEMPLATE)
        {
            m_typeId = "Template";
        }
        else if (!isConnectable(type))
        {
            onConnectionInvalid(type);
            return;
        }
        else
        {
            LOG_DEBUG("Template::setPin :");
            LOG_DEBUG("Set the template type to : {0}", pinTypeToString(type))

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
                    break;
            }

            setType(type);
            dispatch(type);
        }
    }

    void Template::dispatch(EPinType type)
    {
        auto node = dynamic_cast<Node*>(getNode());

        assert(node != nullptr);

        for (PIN sibling : getSiblings())
        {
            auto pin = std::dynamic_pointer_cast<Template>(sibling);

            if (pin && pin->getTemplateID() == m_templateID && pin->getType() != type)
            {
                assert(pin->isConnectable(type));
                pin->setBindedType(type);
            }
        }
    }

    void Template::onConnectionInvalid(EPinType type) const
    {
        LOG_ERROR("Template::setPin : ");
        LOG_ERROR("Invalid pin type : the IN type can be :");
        for (EPinType connectableType : m_connectableTypes)
        {
            LOG_ERROR(pinTypeToString(connectableType));
        }
        LOG_ERROR("And not : {0}.", pinTypeToString(type));
    }

    std::list<std::shared_ptr<Template>> Template::getSiblings()
    {
        auto node = dynamic_cast<Node*>(getNode());

        assert(node != nullptr);

        std::list<std::shared_ptr<Template>> output;

        for (PIN in : node->inputs())
        {
            auto pin = std::dynamic_pointer_cast<Template>(in);
            if (pin && pin->getTemplateID() == m_templateID) output.push_back(pin);
        }

        for (PIN out : node->outputs())
        {
            auto pin = std::dynamic_pointer_cast<Template>(out);
            if (pin && pin->getTemplateID() == m_templateID) output.push_back(pin);
        }

        return output;
    }
}