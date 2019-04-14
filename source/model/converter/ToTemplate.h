#ifndef SHADERGRAPH_TOTEMPLATE_H
#define SHADERGRAPH_TOTEMPLATE_H

#include <nodes/TypeConverter>
#include <nodes/DataModelRegistry>

#include "../Node.h"
#include "../../pin/PinDecl.h"

namespace ShaderGraph
{
    void registerToTemplateConverters(std::shared_ptr<QtNodes::DataModelRegistry> registry);

    class BoolToTemplate
    {
    public:
        PIN operator()(const PIN data);

    private:
        PIN m_out;
    };

    class FloatToTemplate
    {
    public:
        PIN operator()(const PIN data);

    private:
        PIN m_out;
    };

    class Vec2ToTemplate
    {
    public:
        PIN operator()(const PIN data);

    private:
        PIN m_out;
    };

    class Vec3ToTemplate
    {
    public:
        PIN operator()(const PIN data);

    private:
        PIN m_out;
    };

    class Vec4ToTemplate
    {
    public:
        PIN operator()(const PIN data);

    private:
        PIN m_out;
    };
}

#endif //SHADERGRAPH_TOTEMPLATE_H
