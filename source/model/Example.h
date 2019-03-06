#ifndef SHADERGRAPH_EXAMPLE_H
#define SHADERGRAPH_EXAMPLE_H

#include <memory>

#include "Node.h"

namespace ShaderGraph
{
    class Example : public Node
    {
        Q_OBJECT

    public:
        Example() : Node("Example")
        {
            inputs() = std::vector<PIN>{
                std::make_shared<Float>(),
                std::make_shared<Boolean>()
            };

            outputs() = std::vector<PIN>{
                std::make_shared<Float>(),
                std::make_shared<Vector2>()
            };
        }
    };
}

#endif //SHADERGRAPH_EXAMPLE_H
