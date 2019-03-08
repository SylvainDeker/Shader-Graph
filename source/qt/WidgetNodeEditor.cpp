//
// Created by Valentin on 2019-02-21.
//

#include "WidgetNodeEditor.h"

#include "../model/NodeManager.h"

#include "../model/Example.h"
#include "../model/ColorNode.h"


WidgetNodeEditor::WidgetNodeEditor(QWidget *parent):
    QWidget(parent)
{
    ShaderGraph::NodeManager nodeManager;

    nodeManager.loadNodeStyle("../data/nodestyle.txt");

    nodeManager.registry()->registerModel<ShaderGraph::Example>("Test");
    nodeManager.registry()->registerModel<ShaderGraph::ColorNode>("Input");

    m_layout        = new QVBoxLayout(this);
    m_scene         = new FlowScene(nodeManager.registry(),this);
    m_graphicsView  = new FlowView(m_scene);

    m_layout->addWidget(m_graphicsView);
}
