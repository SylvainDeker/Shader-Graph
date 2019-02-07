//
// Created by Valentin on 2019-02-07.
//

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include <memory>

namespace ShaderGraph
{
    class FloatNodeData : public QtNodes::NodeData
    {
    public:

        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType {"Float", "Float"};
        }
    };
}