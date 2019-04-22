#include "Math.h"

namespace ShaderGraph
{
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