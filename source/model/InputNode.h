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
    public:
        QWidget * embeddedWidget() override ;
    protected:
        InputNode(QString name = "Input", QString caption="Input");
        QWidget * m_mainwidget;
        QBoxLayout * m_layout;
        double m_spinbox_step = 0.1;
        double m_spinbox_min = -10e30;
        double m_spinbox_max = 10e30;
    };
}

#endif //SHADERGRAPH_INPUTNODE_H
