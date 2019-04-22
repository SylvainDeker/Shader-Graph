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
            Pin::connect(inPin);
            node->setValidation(NodeValidationState::Valid);
            setBindedType(pin->getType(), true);
        }
    }

    /// Disconnect this pin.
    void Template::disconnect()
    {
        Pin::disconnect();

        auto node = dynamic_cast<Node*>(getNode());

        // Note : Only for debug -- The number of connected pin is useless otherwise.
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

        if (connectedPinsCount == 0)
        {
            for (PIN sibling : getSiblings())
            {
                auto pin = std::dynamic_pointer_cast<Template>(sibling);
                assert(pin != nullptr);
                pin->setBindedType(EPinType::TEMPLATE);
            }
        }
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

    void Template::setBindedType(EPinType type, bool doDispatch)
    {
        if (type == EPinType::TEMPLATE)
        {
            setType(type);
            m_typeId = "Template";
        }
        else if (!isConnectable(type))
        {
            onConnectionInvalid(type);
            return;
        }
        else
        {
            if (doDispatch)
            {
                setType(type);
                dispatch(type);
            }
            else
            {
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
            }
        }
    }

    void Template::dispatch(EPinType type)
    {
        auto node = dynamic_cast<Node*>(getNode());

        assert(node != nullptr);

        for (PIN sibling : getSiblings())
        {
            auto pin = std::dynamic_pointer_cast<Template>(sibling);

            if (pin && pin->getTemplateID() == m_templateID)
            {
                assert(pin->isConnectable(type));

                pin->setBindedType(type, false);
            }
        }
    }

    void Template::onConnectionInvalid(EPinType type) const
    {
        LOG_DEBUG("Template::setPin : ");
        LOG_ERROR("Invalid pin type :");
        LOG_ERROR("This node can be connected to : ")
        for (EPinType connectableType : m_connectableTypes)
        {
            LOG_ERROR("* {0}", pinTypeToString(connectableType));
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
