#ifndef SHADERGRAPH_BOOLPIN_H
#define SHADERGRAPH_BOOLPIN_H

#include <core/Core.h>

#include "Pin.h"

namespace ShaderGraph
{
    class Boolean : public GenType<bool>
    {
    public:
        /// Default constructor.
        explicit Boolean(QString name = "Boolean", QtNodes::NodeDataModel * owner = nullptr) :
                GenType<bool>(false, name, owner, EPinType::BOOLEAN)
        {

        };

        /// Constructor.
        explicit Boolean(bool value, QString name = "Boolean", QtNodes::NodeDataModel * owner = nullptr) :
                GenType<bool>(value, name, owner, EPinType::BOOLEAN)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Boolean", name()};
        }

        /// @return : Get the GLSL type (in string) which represents this pin.
        std::string typeToGLSL() override { return "bool"; }

        /// @return : Get the GLSL default value in string,
        /// if this pin isn't connected during code generation.
        std::string defaultValueToGLSL() override { return "false"; }
    };
}

#endif //SHADERGRAPH_BOOLPIN_H
