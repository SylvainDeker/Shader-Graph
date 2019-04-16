#ifndef SHADERGRAPH_MASTERMATERIALOUTPUT_H
#define SHADERGRAPH_MASTERMATERIALOUTPUT_H

#include "../Node.h"
#include "pin/Pin.h"

namespace ShaderGraph
{
    class MasterMaterialOutput : public Node
    {
    public:
        MasterMaterialOutput() : Node("MasterMaterialOutput")
        {
            inputs() = std::vector<PIN> {
                std::make_shared<Vector3>("Diffuse", this),
                std::make_shared<Vector3>("Normal", this),
                std::make_shared<Vector3>("Specular", this),

                std::make_shared<Float>("Metallic", this),
                std::make_shared<Float>("Roughness", this),
                std::make_shared<Float>("Emissive", this),
                std::make_shared<Float>("Opacity", this),

                std::make_shared<Vector3>("WorldPositionOffset", this),
                std::make_shared<Vector3>("AmbientOcclusion", this),
                std::make_shared<Vector3>("Refraction", this),
                std::make_shared<Vector2>("TextureCoordinate", this),
                std::make_shared<Vector3>("Tangent", this),
                std::make_shared<Float>("Depth", this)
            };
        }

        inline std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "// End MasterMaterialOutput",
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }

        inline std::string toGLSL() override
        {
            std::list<unsigned int> nodes;
            std::string glslCode  = inputsToGLSL(nodes) + nodeToGLSL();
            return glslCode;
        }

        inline std::string autoName(PIN pin) override
        {
            return pin->type().name.toStdString();
        }
    };
}

#endif //SHADERGRAPH_MASTERMATERIALOUTPUT_H
