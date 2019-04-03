#ifndef SHADERGRAPH_ABSTRACTOR_H
#define SHADERGRAPH_ABSTRACTOR_H

#include "../Node.h"

#include "ToTemplate.h"

namespace ShaderGraph
{
    class FxVecN : public Node
    {
    public:
        FxVecN() : Node("FxVecN")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(std::vector<EPinType> {FLOAT, VEC2, VEC3, VEC4},
                                               0,
                                               "Result",
                                               this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(std::vector<EPinType> {FLOAT, VEC2, VEC3, VEC4},
                                               0,
                                               "Input",
                                               this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer, "Hello");
            return buffer;
        }
    };

    class GxOnlyVec2 : public Node
    {
    public:
        GxOnlyVec2() : Node("GxOnlyVec2")
        {
            outputs() = std::vector<PIN> {
                    std::make_shared<Template>(std::vector<EPinType> {VEC2}, 0, "Result", this)
            };

            inputs() = std::vector<PIN> {
                    std::make_shared<Template>(std::vector<EPinType> {VEC2}, 0, "Input", this)
            };
        }

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer, "Hello");
            return buffer;
        }
    };
}

#endif //SHADERGRAPH_ABSTRACTOR_H
