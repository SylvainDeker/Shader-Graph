#ifndef SHADERGRAPH_OUTPUTNODE_H
#define SHADERGRAPH_OUTPUTNODE_H

#include "Node.h"

namespace ShaderGraph
{
    class OutputNode : public Node
    {
    Q_OBJECT

    public:
        /// Constructor.
        OutputNode(QString name, QString caption) : Node(name, caption) {}

        /// Destructor.
        ~OutputNode() override = default;
    };
}


#endif //SHADERGRAPH_OUTPUTNODE_H
