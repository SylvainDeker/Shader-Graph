#include "ToTemplate.h"

namespace ShaderGraph
{
    void registerToTemplateConverters(std::shared_ptr<QtNodes::DataModelRegistry> registry)
    {
        registry->registerModel<ShaderGraph::BoolToTemplate>("Converter");
        registry->registerModel<ShaderGraph::ScalarToTemplate>("Converter");
        registry->registerModel<ShaderGraph::Vec2ToTemplate>("Converter");
        registry->registerModel<ShaderGraph::Vec3ToTemplate>("Converter");
        registry->registerModel<ShaderGraph::Vec4ToTemplate>("Converter");
    }
}