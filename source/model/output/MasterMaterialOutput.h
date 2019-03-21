#ifndef SHADERGRAPH_MASTERMATERIALOUTPUT_H
#define SHADERGRAPH_MASTERMATERIALOUTPUT_H

#include "../Node.h"
#include "../Data.h"

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

                std::make_shared<Vector3>("Metallic", this),
                std::make_shared<Vector3>("Roughness", this),
                std::make_shared<Vector3>("Emissive", this),

                std::make_shared<Vector3>("Opacity", this),

                std::make_shared<Vector3>("World Position Offset", this),

                std::make_shared<Vector3>("Ambient Occlusion", this),

                std::make_shared<Vector3>("Refraction", this),

                std::make_shared<Vector2>("Texture Coordinate", this),

                std::make_shared<Vector3>("Tangent", this),

                std::make_shared<Float>("Depth", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "MASTER_MATERIAL_OUTPUT({0}, {1}, ...);",
                      autoName(inputs()[0]),
                      autoName(inputs()[1]));
            return buffer;
        }
    };
}

#endif //SHADERGRAPH_MASTERMATERIALOUTPUT_H
