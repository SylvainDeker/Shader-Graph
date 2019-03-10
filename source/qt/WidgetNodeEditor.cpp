#include "WidgetNodeEditor.h"

#include "model/manager/NodeManager.h"

#include "model/NodeDecl.h"

WidgetNodeEditor::WidgetNodeEditor(QWidget *parent):
    QWidget(parent)
{
    ShaderGraph::NodeManager nodeManager;

    nodeManager.loadNodeStyle("../data/nodestyle.txt");

    nodeManager.registry()->registerModel<ShaderGraph::MasterMaterialOutput>("Output");

    nodeManager.registry()->registerModel<ShaderGraph::ColorNode>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::TextureNode>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::ScalarNode>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::Vec2Node>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::Vec3Node>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::Vec4Node>("Input");

    nodeManager.registry()->registerModel<ShaderGraph::MakeVec2Node>("Vector");
    nodeManager.registry()->registerModel<ShaderGraph::BreakVec2Node>("Vector");
    nodeManager.registry()->registerModel<ShaderGraph::MakeVec3Node>("Vector");
    nodeManager.registry()->registerModel<ShaderGraph::BreakVec3Node>("Vector");
    nodeManager.registry()->registerModel<ShaderGraph::MakeVec4Node>("Vector");
    nodeManager.registry()->registerModel<ShaderGraph::BreakVec4Node>("Vector");

    m_layout        = new QVBoxLayout(this);
    m_scene         = new FlowScene(nodeManager.registry(),this);
    m_graphicsView  = new FlowView(m_scene);

    m_layout->addWidget(m_graphicsView);
}
