#ifndef SHADERGRAPH_FLOATPIN_H
#define SHADERGRAPH_FLOATPIN_H

#include <core/Core.h>

#include "Pin.h"

namespace ShaderGraph
{
    class Float : public GenType<float>
    {
    public:
        /// Default constructor.
        explicit Float(QString name = "Float", QtNodes::NodeDataModel * owner = nullptr) :
                GenType<float>(0.0f, name, owner, EPinType::FLOAT)
        {

        };

        /// Constructor.
        explicit Float(float value, QString name = "Float", QtNodes::NodeDataModel * owner = nullptr) :
                GenType<float>(value, name, owner, EPinType::FLOAT)
        {

        };

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Float", name()};
        }

        /// @return : Get the GLSL type (in string) which represents this pin.
        std::string typeToGLSL() override { return "float"; }

        // TODO : comment me :)
        std::string defaultValueToGLSL() override { return "0.0f"; }
    };
}

#endif //SHADERGRAPH_FLOATPIN_H
