#ifndef SHADERGRAPH_FLOWSCENE_H
#define SHADERGRAPH_FLOWSCENE_H

#include <nodes/Node>
#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>
#include <nodes/TypeConverter>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include <core/Core.h>

#include "model/Node.h"

namespace ShaderGraph
{
    class FlowScene : public QtNodes::FlowScene
    {
        Q_OBJECT

    public:

        explicit FlowScene(std::shared_ptr<QtNodes::DataModelRegistry> registry, QObject * parent = Q_NULLPTR) :
            QtNodes::FlowScene(registry, parent)
        {

        }

        explicit FlowScene(QObject * parent = Q_NULLPTR) :
            QtNodes::FlowScene(parent)
        {

        }

        ~FlowScene() override = default;
    };

}

#endif //SHADERGRAPH_FLOWSCENE_H
