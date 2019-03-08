#ifndef SHADERGRAPH_INPUTNODE_H
#define SHADERGRAPH_INPUTNODE_H

#include <memory>
#include <QBoxLayout>
#include "Node.h"

namespace ShaderGraph
{
    class InputNode : public Node
    {
        Q_OBJECT

    protected:
        InputNode(QString name = "Input", QString caption="Input");
        QWidget * m_mainwidget;
        QBoxLayout * m_layout;
    };
}

#endif //SHADERGRAPH_INPUTNODE_H
