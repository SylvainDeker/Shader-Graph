#ifndef SHADERGRAPH_VECTORFUNCTIONS_H
#define SHADERGRAPH_VECTORFUNCTIONS_H

#include "../Node.h"
#include "../Data.h"

namespace ShaderGraph
{
    class MakeVec2Node : public Node
    {
    public:
        MakeVec2Node() : Node("MakeVec2")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Vector2>()
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("X"),
                    std::make_shared<Float>("Y")
            };
        }
    };

    class MakeVec3Node : public Node
    {
    public:
        MakeVec3Node() : Node("MakeVec3")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Vector3>()
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("X"),
                    std::make_shared<Float>("Y"),
                    std::make_shared<Float>("Z")
            };
        }
    };

    class MakeVec4Node : public Node
    {
    public:
        MakeVec4Node() : Node("MakeVec4")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Vector4>()
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("X"),
                    std::make_shared<Float>("Y"),
                    std::make_shared<Float>("Z"),
                    std::make_shared<Float>("A")
            };
        }
    };

    class BreakVec2Node : public Node
    {
    public:
        BreakVec2Node() : Node("BreakVec2")
        {
            inputs() = std::vector<PIN> {
                std::make_shared<Vector2>()
            };

            outputs() = std::vector<PIN> {
                std::make_shared<Float>("X"),
                std::make_shared<Float>("Y")
            };
        }
    };

    class BreakVec3Node : public Node
    {
    public:
        BreakVec3Node() : Node("BreakVec3")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector3>()
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("X"),
                    std::make_shared<Float>("Y"),
                    std::make_shared<Float>("Z")
            };
        }
    };

    class BreakVec4Node : public Node
    {
    public:
        BreakVec4Node() : Node("BreakVec4")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector4>()
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("X"),
                    std::make_shared<Float>("Y"),
                    std::make_shared<Float>("Z"),
                    std::make_shared<Float>("A")
            };
        }
    };
}

#endif //SHADERGRAPH_VECTORFUNCTIONS_H
