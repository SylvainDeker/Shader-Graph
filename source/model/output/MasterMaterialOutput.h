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
                std::make_shared<Vector3>("Diffuse"),
                std::make_shared<Vector3>("Normal"),

                std::make_shared<Vector3>("Metallic"),
                std::make_shared<Vector3>("Roughness"),
                std::make_shared<Vector3>("Emissive"),

                std::make_shared<Vector3>("Opacity"),

                std::make_shared<Vector3>("World Position Offset"),

                std::make_shared<Vector3>("Ambient Occlusion"),

                std::make_shared<Vector3>("Refraction"),

                std::make_shared<Vector2>("Texture Coordinate"),

                std::make_shared<Vector3>("Tangent"),

                std::make_shared<Float>("Depth")
            };
        }
    };
}

#endif //SHADERGRAPH_MASTERMATERIALOUTPUT_H
