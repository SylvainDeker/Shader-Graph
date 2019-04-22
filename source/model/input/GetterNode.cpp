#include "GetterNode.h"

namespace ShaderGraph
{
    UVNode::UVNode() : Node("UVs", "UVs")
    {
        outputs() = std::vector<PIN>{
                std::make_shared<Vector2>("UVs", this),
                std::make_shared<Float>("u", this),
                std::make_shared<Float>("v", this)
        };
    }

    StepNode::StepNode() : Node("Step", "Step")
    {
        inputs() = std::vector<PIN>{
                std::make_shared<Float>("Value", this),
                std::make_shared<Float>("Step", this)
        };

        outputs() = std::vector<PIN>{
                std::make_shared<Float>("Result", this)
        };
    }
}