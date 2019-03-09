//
// Created by Valentin on 2019-02-21.
//

#include "WidgetNodeEditor.h"

#include "../model/NodeManager.h"

#include "../model/Example.h"
#include "../model/ColorNode.h"

#include "../model/Vec2Node.h"
#include "../model/Vec3Node.h"
#include "../model/Vec4Node.h"
#include "../model/ScalarNode.h"



WidgetNodeEditor::WidgetNodeEditor(QWidget *parent):
    QWidget(parent)
{
    ShaderGraph::NodeManager nodeManager;

    nodeManager.loadNodeStyle("../data/nodestyle.txt");

    nodeManager.registry()->registerModel<ShaderGraph::Example>("Test");
    nodeManager.registry()->registerModel<ShaderGraph::ColorNode>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::ScalarNode>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::Vec2Node>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::Vec3Node>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::Vec4Node>("Input");

    m_layout        = new QVBoxLayout(this);
    m_scene         = new FlowScene(nodeManager.registry(),this);
    m_graphicsView  = new FlowView(m_scene);

    m_layout->addWidget(m_graphicsView);
}
