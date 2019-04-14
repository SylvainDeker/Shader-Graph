#include "ToTemplate.h"

#include <cassert>

#define MAKE_TEMPLATE std::make_shared<Template>

namespace ShaderGraph
{
    void registerToTemplateConverters(std::shared_ptr<QtNodes::DataModelRegistry> registry)
    {
        auto pair = std::make_pair(Boolean().type(), Template(EPinType::TEMPLATE).type());
        auto converter = QtNodes::TypeConverter{ShaderGraph::BoolToTemplate()};
        registry->registerTypeConverter(pair, converter);

        pair = std::make_pair(Float().type(), Template(EPinType::TEMPLATE).type());
        converter = QtNodes::TypeConverter{ShaderGraph::FloatToTemplate()};
        registry->registerTypeConverter(pair, converter);

        pair = std::make_pair(Vector2().type(), Template(EPinType::TEMPLATE).type());
        converter = QtNodes::TypeConverter{ShaderGraph::Vec2ToTemplate()};
        registry->registerTypeConverter(pair, converter);

        pair = std::make_pair(Vector3().type(), Template(EPinType::TEMPLATE).type());
        converter = QtNodes::TypeConverter{ShaderGraph::Vec3ToTemplate()};
        registry->registerTypeConverter(pair, converter);

        pair = std::make_pair(Vector4().type(), Template(EPinType::TEMPLATE).type());
        converter = QtNodes::TypeConverter{ShaderGraph::Vec4ToTemplate()};
        registry->registerTypeConverter(pair, converter);
    }

    PIN BoolToTemplate::operator()(const PIN data)
    {
        auto values = std::vector<std::shared_ptr<Pin>> {
                std::dynamic_pointer_cast<Boolean>(data),
                std::dynamic_pointer_cast<Template>(data)
        };

        if (values[0])
        {
            m_out = MAKE_TEMPLATE(EPinType::BOOLEAN, 0, values[0]->type().name, values[0]->getNode());
        }
        else if (values[1])
        {
            m_out = MAKE_TEMPLATE(EPinType::BOOLEAN, 0, values[1]->type().name, values[1]->getNode());
        }

        return m_out;
    }

    PIN FloatToTemplate::operator()(const PIN data)
    {
        auto values = std::vector<std::shared_ptr<Pin>> {
            std::dynamic_pointer_cast<Float>(data),
            std::dynamic_pointer_cast<Template>(data)
        };

        if (values[0])
        {
            m_out = MAKE_TEMPLATE(EPinType::FLOAT, 0, values[0]->type().name, values[0]->getNode());
        }
        else if (values[1])
        {
            m_out = MAKE_TEMPLATE(EPinType::FLOAT, 0, values[1]->type().name, values[1]->getNode());
        }

        return m_out;
    }

    PIN Vec2ToTemplate::operator()(const PIN data)
    {
        auto values = std::vector<std::shared_ptr<Pin>> {
                std::dynamic_pointer_cast<Vector2>(data),
                std::dynamic_pointer_cast<Template>(data)
        };

        if (values[0])
        {
            m_out = MAKE_TEMPLATE(EPinType::VEC2, 0, values[0]->type().name, values[0]->getNode());
        }
        else if (values[1])
        {
            m_out = MAKE_TEMPLATE(EPinType::VEC2, 0, values[1]->type().name, values[1]->getNode());
        }

        return m_out;
    }

    PIN Vec3ToTemplate::operator()(const PIN data)
    {
        auto values = std::vector<std::shared_ptr<Pin>> {
                std::dynamic_pointer_cast<Vector3>(data),
                std::dynamic_pointer_cast<Template>(data)
        };

        if (values[0])
        {
            m_out = MAKE_TEMPLATE(EPinType::VEC3, 0, values[0]->type().name, values[0]->getNode());
        }
        else if (values[1])
        {
            m_out = MAKE_TEMPLATE(EPinType::VEC3, 0, values[1]->type().name, values[1]->getNode());
        }

        return m_out;
    }

    PIN Vec4ToTemplate::operator()(const PIN data)
    {
        auto values = std::vector<std::shared_ptr<Pin>> {
                std::dynamic_pointer_cast<Vector4>(data),
                std::dynamic_pointer_cast<Template>(data)
        };

        if (values[0])
        {
            m_out = MAKE_TEMPLATE(EPinType::VEC4, 0, values[0]->type().name, values[0]->getNode());
        }
        else if (values[1])
        {
            m_out = MAKE_TEMPLATE(EPinType::VEC4, 0, values[1]->type().name, values[1]->getNode());
        }

        return m_out;
    }
}