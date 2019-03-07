#ifndef SHADERGRAPH_INPUTNODE_H
#define SHADERGRAPH_INPUTNODE_H

#include "Node.h"

namespace ShaderGraph
{
    class InputNode : public Node
    {
        Q_OBJECT

    public:
        /// Constructor.
        InputNode(QString name, QString caption) : Node(name, caption) {}

        /// Destructor.
        ~InputNode() override = default;
    };
}

#endif //SHADERGRAPH_INPUTNODE_H
