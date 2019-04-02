#include "FromTemplate.h"

namespace ShaderGraph
{
    void registerFromTemplateConverters(std::shared_ptr<QtNodes::DataModelRegistry> registry)
    {
        registry->registerModel<ShaderGraph::BoolFromTemplate>("Converter");
        registry->registerModel<ShaderGraph::ScalarFromTemplate>("Converter");
        registry->registerModel<ShaderGraph::Vec2FromTemplate>("Converter");
        registry->registerModel<ShaderGraph::Vec3FromTemplate>("Converter");
        registry->registerModel<ShaderGraph::Vec4FromTemplate>("Converter");
    }
}