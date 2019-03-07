#ifndef SHADERGRAPH_INPUTNODE_H
#define SHADERGRAPH_INPUTNODE_H

#include <memory>

#include "Node.h"

namespace ShaderGraph
{
    class InputNode : public Node
    {
        Q_OBJECT

    protected:
        InputNode(QString name = "Input", QString caption="Input");
    };
}

#endif //SHADERGRAPH_INPUTNODE_H
