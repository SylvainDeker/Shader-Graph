#include "ToTemplate.h"

#include <cassert>

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

    PIN BoolToTemplate::operator()(PIN data)
    {
        auto value = std::dynamic_pointer_cast<Boolean>(data);

        if (value) m_out = std::make_shared<Template>(EPinType::BOOLEAN, 0, "T", value->getNode());

        return m_out;
    }

    PIN FloatToTemplate::operator()(PIN data)
    {
        LOG_DEBUG("Cast :)");

        auto value = std::dynamic_pointer_cast<Float>(data);

        if (value) m_out = std::make_shared<Template>(EPinType::FLOAT, 0, "T", value->getNode());

        return m_out;
    }

    PIN Vec2ToTemplate::operator()(PIN data)
    {
        auto value = std::dynamic_pointer_cast<Vector2>(data);

        if (value) m_out = std::make_shared<Template>(EPinType::VEC2, 0, "T", value->getNode());

        return m_out;
    }

    PIN Vec3ToTemplate::operator()(PIN data)
    {
        auto value = std::dynamic_pointer_cast<Vector3>(data);

        if (value) m_out = std::make_shared<Template>(EPinType::VEC3, 0, "T", value->getNode());

        return m_out;
    }

    PIN Vec4ToTemplate::operator()(PIN data)
    {
        auto value = std::dynamic_pointer_cast<Vector4>(data);

        if (value) m_out = std::make_shared<Template>(EPinType::VEC4, 0, "T", value->getNode());

        return m_out;
    }
}