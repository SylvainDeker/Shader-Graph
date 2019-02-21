//
// Created by Valentin on 2019-02-21.
//

#include "WidgetNodeEditor.h"

#include "../model/NodeManager.h"
#include "../model/input/BooleanNode.h"


WidgetNodeEditor::WidgetNodeEditor(QWidget *parent):
        QWidget(parent)
{
    ShaderGraph::NodeManager nodeManager;
    nodeManager.registry()->registerModel<ShaderGraph::BooleanNode>();

    nodeManager.loadNodeStyle("../data/nodestyle.txt");

    m_layout        = new QVBoxLayout(this);
    m_scene         = new FlowScene(nodeManager.registry(),this);
    m_graphicsView  = new FlowView(m_scene);

    m_layout->addWidget(m_graphicsView);
}