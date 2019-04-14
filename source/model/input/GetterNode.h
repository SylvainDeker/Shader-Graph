#ifndef SHADERGRAPH_GETTERNODE_H
#define SHADERGRAPH_GETTERNODE_H

#include <memory>

#include <core/Core.h>

#include "../Node.h"

#define SPINBOX_STEP 0.1
#define SPINBOX_VALUE_CHANGED_SLOT static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)

namespace ShaderGraph
{
    class UVNode : public Node
    {
    Q_OBJECT

    public:
        UVNode();

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "// Input : UV \n"
                      "{0} = texCoord; \n"
                      "{1} = texCoord.x; \n"
                      "{2} = texCoord.y; \n"
                      "\n",
                      autoName(outputs()[0]),
                      autoName(outputs()[1]),
                      autoName(outputs()[2]));
            return buffer;
        }
    };
}

#endif //SHADERGRAPH_GETTERNODE_H
