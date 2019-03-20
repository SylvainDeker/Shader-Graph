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
                    std::make_shared<Vector2>("Vector2", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("X", this),
                    std::make_shared<Float>("Y", this)
            };
        }

        void showDetails(QVBoxLayout * layout) override
        {
            Node::showDetails( layout );
        }


    };

    class MakeVec3Node : public Node
    {
    public:
        MakeVec3Node() : Node("MakeVec3")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("Vector3", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("X", this),
                    std::make_shared<Float>("Y", this),
                    std::make_shared<Float>("Z", this)
            };
        }

        void showDetails(QVBoxLayout * layout) override
        {
            Node::showDetails(layout);
        }
    };

    class MakeVec4Node : public Node
    {
    public:
        MakeVec4Node() : Node("MakeVec4")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Vector4", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Float>("X", this),
                    std::make_shared<Float>("Y", this),
                    std::make_shared<Float>("Z", this),
                    std::make_shared<Float>("A", this)
            };
        }

        void showDetails(QVBoxLayout * layout) override
        {
            Node::showDetails(layout);
        }
    };

    class BreakVec2Node : public Node
    {
    public:
        BreakVec2Node() : Node("BreakVec2")
        {
            inputs() = std::vector<PIN> {
                std::make_shared<Vector2>("Vector2", this)
            };

            outputs() = std::vector<PIN> {
                std::make_shared<Float>("X", this),
                std::make_shared<Float>("Y", this)
            };
        }

        void showDetails(QVBoxLayout * layout) override
        {
            Node::showDetails(layout);
        }
    };

    class BreakVec3Node : public Node
    {
    public:
        BreakVec3Node() : Node("BreakVec3")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector3>("Vector3", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("X", this),
                    std::make_shared<Float>("Y", this),
                    std::make_shared<Float>("Z", this)
            };
        }

        void showDetails(QVBoxLayout * layout) override
        {
            Node::showDetails(layout);
        }
    };

    class BreakVec4Node : public Node
    {
    public:
        BreakVec4Node() : Node("BreakVec4")
        {
            inputs() = std::vector<PIN> {
                    std::make_shared<Vector4>("Vector4", this)
            };

            outputs() = std::vector<PIN> {
                    std::make_shared<Float>("X", this),
                    std::make_shared<Float>("Y", this),
                    std::make_shared<Float>("Z", this),
                    std::make_shared<Float>("A", this)
            };
        }

        void showDetails(QVBoxLayout * layout) override
        {
            Node::showDetails(layout);
        }
    };
}

#endif //SHADERGRAPH_VECTORFUNCTIONS_H
